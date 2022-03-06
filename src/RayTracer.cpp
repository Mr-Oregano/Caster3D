
#include "RayTracer.h"

#include "Ray.h"
#include "Triangle.h"
#include "Material.h"

#include <glm/gtx/intersect.hpp>

RayTracer::RayTracer(const std::shared_ptr<Scene> &scene)
	: _scene(scene)
{}

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

glm::dvec3 RayTracer::CalcColor(const Ray &ray, int max_bounces)
{
	HitResult result = RayCast(ray, 100.0);
	
	if (!result)
		// NOTE: Raycast failed, return skybox color
		//
		return glm::dvec3{ 0.0 };

	glm::dvec3 color = result.material.color * result.triangle.color;
	
	// NOTE: We need to add a slight bias to the shadow ray origin
	//		 in order to reduce surface acne.
	//
	constexpr double bias = 0.001;
	glm::dvec3 new_origin = result.hit_point - bias * ray.dir;
	glm::dvec3 light_contribution{ 0.0 };

	for (const Light &light : _scene->GetLights())
	{
		double light_dist = glm::distance(result.hit_point, light.pos);
		glm::dvec3 light_dir = glm::normalize(light.pos - result.hit_point);
		double light_factor = glm::dot(result.triangle.normal, light_dir);

		bool behind_light = light_factor <= 0.0;
		Ray shadow_cast(new_origin, light.pos);

		// NOTE: Short circuit; if the object is behind the light don't waste any effort ray casting.
		//
		if (!behind_light && RayCast(shadow_cast, 100.0).distance >= light_dist)
			light_contribution += light.color * light_factor;
	}

	light_contribution /= _scene->GetLights().size();

	if (max_bounces > 0 && result.material.reflection > 0.0)
	{
		Ray reflection_cast;
		reflection_cast.origin = new_origin;
		reflection_cast.dir = glm::reflect(ray.dir, result.triangle.normal);
		glm::dvec3 reflection = CalcColor(reflection_cast, max_bounces - 1);
		return glm::mix(color * light_contribution, reflection, result.material.reflection);
	}

	return color * light_contribution;
}

void RayTracer::Draw(ImageBuffer &image_buffer)
{
	auto [ width, height ] = image_buffer.GetExtent();
	const Camera &cam = _scene->GetCamera();

	double distance = 1.0 / glm::tan(glm::radians(cam.GetFOV() / 2.0));
	glm::dvec3 t = glm::normalize(cam.GetTarget() - cam.GetEye());
	glm::dvec3 b = glm::cross(t, cam.GetUp());
	glm::dvec3 v = glm::cross(t, b);

	glm::dvec3 qx = (2.0 / width) * b;
	glm::dvec3 qy = (2.0 / height) * v;
	glm::dvec3 plm = t * distance - b - v;

	for (std::uint32_t i = 0; i < width * height; ++i)
	{
		double x = i % width;
		double y = i / width;

		Ray ray;
		ray.origin = cam.GetEye();
		ray.dir = glm::normalize(plm + qx * x + qy * y);

		glm::dvec3 color = CalcColor(ray, 16);

		image_buffer.WritePixel(i, color.r, color.g, color.b);
	}
}
