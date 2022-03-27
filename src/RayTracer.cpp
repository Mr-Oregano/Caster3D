
#include "RayTracer.h"

#include "Ray.h"
#include "Triangle.h"
#include "Material.h"

const double RayTracer::RAYCAST_DIST = std::numeric_limits<double>::infinity();

RayTracer::RayTracer(const RayTracerConfig &config)
	: _config(config)
{}

Color RayTracer::CalcColor(const Ray &ray, int max_bounces)
{
	Scene &scene = *_config.scene;
	HitResult result = _config.scene->RayCast(ray, RAYCAST_DIST);
	
	if (!result)
		// NOTE: Raycast failed, return skybox color
		//
		return _config.skybox;

	Material m = result.material;
	Triangle t = result.triangle;
	
	// NOTE: We need to add a slight bias to the shadow ray origin
	//		 in order to reduce surface acne.
	//
	Vec3 new_origin = result.hit_point - 0.001 * ray.dir;
	Color color{ 0.0 };

	for (const auto &light : scene.GetPointLights())
	{
		Vec3 light_dir = light.CalcDir(result.hit_point);

		if (glm::dot(t.normal, light_dir) <= 0.0)
			continue;

		color += light.CalcContribution(result.hit_point, -ray.dir, t.normal, m) * m.color * t.color;
		
		Ray shadow_cast(new_origin, light_dir);
		HitResult shadow_hit = scene.RayCast(shadow_cast, RAYCAST_DIST);
		if (shadow_hit && shadow_hit.distance < light.CalcDistance(result.hit_point))
			color *= shadow_hit.material.transmission;
	}

	for (const auto &light : scene.GetDirLights())
	{
		if (glm::dot(t.normal, -light.dir) <= 0.0)
			continue;

		color += light.CalcContribution(result.hit_point, -ray.dir, t.normal, m) * m.color * t.color;
		
		Ray shadow_cast(new_origin, -light.dir);
		HitResult shadow_hit = scene.RayCast(shadow_cast, RAYCAST_DIST);
		if (shadow_hit)
			color *= shadow_hit.material.transmission;
	}

	if (max_bounces == 0)
		return color;

	if (m.reflection > 0.0 && m.transmission < 1.0)
	{
		Ray reflected(new_origin, glm::reflect(ray.dir, t.normal));
		Color reflection = CalcColor(reflected, max_bounces - 1);
		color = glm::mix(color, reflection, m.reflection);
	}

	if (m.transmission > 0.0)
	{
		double dot = glm::dot(ray.dir, t.normal);
		Vec3 normal = -t.normal;
		double eta = m.refractive_index;

		if (dot < 0.0)
		{
			// NOTE: We are entering this object
			eta = 1.0 / m.refractive_index;
			normal = -normal;
		}

		Vec3 ref_dir = glm::refract(ray.dir, normal, eta);
		
		if (ref_dir == glm::zero<Vec3>())
			// NOTE: Total internal reflection!
			ref_dir = glm::reflect(ray.dir, t.normal);

		Ray refracted(result.hit_point + 0.001 * ray.dir, ref_dir);
		Color refraction = CalcColor(refracted, max_bounces - 1);
		color = glm::mix(color, refraction, m.transmission);
	}

	return color;
}

void RayTracer::Draw(ImageBuffer &image_buffer)
{
	auto [ width, height ] = image_buffer.GetExtent();
	const Camera &cam = _config.scene->GetCamera();

	double distance = 1.0 / glm::tan(glm::radians(cam.GetFOV() / 2.0));
	Vec3 t = glm::normalize(cam.GetTarget() - cam.GetEye());
	Vec3 b = glm::cross(t, cam.GetUp());
	Vec3 v = glm::cross(t, b);

	Vec3 qx = (2.0 / width) * b;
	Vec3 qy = (2.0 / height) * v;
	Vec3 bottom_left = t * distance - b - v;

	int samples_sqr = _config.samples * _config.samples;

	for (std::uint32_t i = 0; i < width * height; ++i)
	{
		Color color{ 0.0 };

		for (int s = 0; s < samples_sqr; ++s)
		{
			double sx = (double) (s % _config.samples) / _config.samples;
			double sy = (double) (s / _config.samples) / _config.samples;
			double x = (double) (i % width) + sx;
			double y = (double) (i / width) + sy;

			Ray ray(cam.GetEye(), glm::normalize(bottom_left + qx * x + qy * y));
			color += CalcColor(ray, _config.ray_depth);
		}

		color /= samples_sqr;

		image_buffer.WritePixel(i, color.r, color.g, color.b);
	}
}
