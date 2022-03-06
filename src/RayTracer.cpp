
#include "RayTracer.h"

#include "Ray.h"
#include "Triangle.h"
#include "Material.h"

#include <glm/gtx/intersect.hpp>

RayTracer::RayTracer(const std::shared_ptr<Scene> &scene)
	: _scene(scene)
{}

glm::dvec3 PhongShading(const Light &light, glm::dvec3 loc, glm::dvec3 n, glm::dvec3 view_dir, const Material &mat)
{
	glm::dvec3 light_dir = glm::normalize(light.pos - loc);
	glm::dvec3 reflected_light = glm::reflect(-light_dir, n);

	double diff = glm::max(glm::dot(n, light_dir), 0.0);
	double spec = glm::max(glm::dot(view_dir, reflected_light), 0.0);

	return (mat.spec_strength * glm::pow(spec, mat.shininess) + diff + mat.amb_strength) * light.color * mat.color;
}

HitResult RayTracer::RayCast(const Ray &ray, double max_distance)
{
	HitResult result;
	result.distance = max_distance;

	// NOTE: Traverse all triangle lists in scene and find the raycast hit with 
	//		 smallest distance.
	// 
	// TODO: Use bounding volume hierarchy to make this more efficient.
	//
	for (const auto &m : _scene->GetMeshes())
	{
		for (const Triangle &t : m->GetTriangleList())
		{
			glm::dvec2 bari_center;           
			double distance = max_distance;
			bool raycast_hit = glm::intersectRayTriangle(ray.origin, ray.dir, t.v0, t.v1, t.v2, bari_center, distance);
			
			if (raycast_hit && glm::zero<double>() < distance && distance < result.distance)
			{
				result.triangle = t;
				result.material = m->GetMaterial();
				result.distance = distance;
				result.hit_point = ray.GetPoint(distance);
				result.bari = glm::vec3 { bari_center, 1.0f - bari_center.x - bari_center.y };
				result.hit = true;
			}
		}
	}
	
	return result;
}

glm::vec3 RayTracer::CalcColor(const Ray &ray)
{
	HitResult result = RayCast(ray, 100.0);
	
	if (!result)
		// NOTE: Raycast failed, return skybox color
		//
		return glm::vec3{ 0.0f };

	Triangle t = result.triangle;
	glm::dvec3 output_color{ 0.0 };

	for (const Light &light : _scene->GetLights())
	{
		double light_dist = glm::distance(result.hit_point, light.pos);
		glm::dvec3 light_dir = glm::normalize(light.pos - result.hit_point);
		glm::dvec3 phong = PhongShading(light, result.hit_point, t.normal, -ray.dir, result.material) * t.color;

		// NOTE: We need to add a slight bias to the shadow ray origin
		//		 in order to reduce surface acne.
		//
		constexpr double bias = 100.0 * glm::epsilon<double>();
		Ray shadow_cast(result.hit_point - bias * ray.dir, light.pos);

		bool behind_light = glm::dot(t.normal, light_dir) <= 0.0;
		
		// NOTE: Short circuit; if the object is behind the light don't waste any effort ray casting.
		//
		bool in_shadow = behind_light || RayCast(shadow_cast, 100.0).distance < light_dist;
		double shadow = in_shadow ? 0.3 : 1.0;

		output_color += phong * shadow;
	}

	return output_color / (double) _scene->GetLights().size();
}

void RayTracer::Draw(ImageBuffer &image_buffer)
{
	auto [ width, height ] = image_buffer.GetExtent();
	std::uint8_t px_stride = image_buffer.GetBytesPerPixel();

	const Camera &cam = _scene->GetCamera();

	double distance = 1.0 / glm::tan(glm::radians(cam.GetFOV() / 2.0));
	glm::dvec3 t = glm::normalize(cam.GetTarget() - cam.GetEye());
	glm::dvec3 b = glm::cross(t, cam.GetUp());
	glm::dvec3 v = glm::cross(t, b);

	glm::dvec3 qx = (2.0 / width) * b;
	glm::dvec3 qy = (2.0 / height) * v;
	glm::dvec3 plm = t * distance - b - v;

	for (std::uint32_t i = 0; i < image_buffer.GetBufferSize(); i += px_stride)
	{
		double x = (i / px_stride) % width;
		double y = (i / px_stride) / width;

		Ray ray;
		ray.origin = cam.GetEye();
		ray.dir = glm::normalize(plm + qx * x + qy * y);

		glm::dvec3 color = CalcColor(ray);

		image_buffer.WritePixel(i, color.r, color.g, color.b);
	}
}
