
#include "RayTracer.h"

#include "Ray.h"
#include "Triangle.h"
#include "Material.h"

RayTracer::RayTracer(const std::shared_ptr<Scene> &scene)
	: _scene(scene)
{}

Color RayTracer::CalcColor(const Ray &ray, int max_bounces)
{
	HitResult result = _scene->RayCast(ray, 100.0);
	
	if (!result)
		// NOTE: Raycast failed, return skybox color
		//
		return { 0.5, 0.9, 1.0 };

	Material m = result.material;
	Triangle t = result.triangle;
	
	// NOTE: We need to add a slight bias to the shadow ray origin
	//		 in order to reduce surface acne.
	//
	constexpr double bias = 0.001;
	Vec3 new_origin = result.hit_point - bias * ray.dir;
	Color color{ 0.0 };

	for (const auto &light : _scene->GetPointLights())
	{
		Vec3 light_dir = light.CalcDir(result.hit_point);

		if (glm::dot(t.normal, light_dir) <= 0.0)
			continue;

		Ray shadow_cast(new_origin, light_dir);
		if (_scene->RayCast(shadow_cast, 100.0).distance >= light.CalcDistance(result.hit_point))
			color += light.CalcContribution(result.hit_point, -ray.dir, t.normal, m) * m.color * t.color;
	}

	for (const auto &light : _scene->GetDirLights())
	{
		if (glm::dot(t.normal, -light.dir) <= 0.0)
			continue;

		Ray shadow_cast(new_origin, -light.dir);
		if (!_scene->RayCast(shadow_cast, 100.0))
			color += light.CalcContribution(result.hit_point, -ray.dir, t.normal, m) * m.color * t.color;
	}

	if (max_bounces > 0 && m.reflection > 0.0)
	{
		Ray reflection_cast(new_origin, glm::reflect(ray.dir, t.normal));
		Color reflection = CalcColor(reflection_cast, max_bounces - 1);
		return glm::mix(color, reflection, m.reflection);
	}

	return color;
}

void RayTracer::Draw(ImageBuffer &image_buffer, int samples)
{
	auto [ width, height ] = image_buffer.GetExtent();
	const Camera &cam = _scene->GetCamera();

	double distance = 1.0 / glm::tan(glm::radians(cam.GetFOV() / 2.0));
	Vec3 t = glm::normalize(cam.GetTarget() - cam.GetEye());
	Vec3 b = glm::cross(t, cam.GetUp());
	Vec3 v = glm::cross(t, b);

	Vec3 qx = (2.0 / width) * b;
	Vec3 qy = (2.0 / height) * v;
	Vec3 bottom_left = t * distance - b - v;

	int samples_sqr = samples * samples;

	for (std::uint32_t i = 0; i < width * height; ++i)
	{
		Color color{ 0.0 };

		for (int s = 0; s < samples_sqr; ++s)
		{
			double sx = (double) (s % samples) / samples;
			double sy = (double) (s / samples) / samples;
			double x = (double) (i % width) + sx;
			double y = (double) (i / width) + sy;

			Ray ray(cam.GetEye(), glm::normalize(bottom_left + qx * x + qy * y));
			color += CalcColor(ray, 16);
		}

		color /= samples_sqr;

		image_buffer.WritePixel(i, color.r, color.g, color.b);
	}
}
