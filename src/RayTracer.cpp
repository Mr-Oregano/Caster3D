
#include "RayTracer.h"
#include "Metrics.h"

#include <iostream>
#include <random>
#include <functional>
#include <thread>

RayTracer::RayTracer(const RayTracerConfig &config)
	: _config(config)
{}

Color RayTracer::CalcColor(const Ray &ray, int max_bounces)
{
	Scene &scene = *_config.scene;
	HitResult result = _config.scene->RayCast(ray);
	
	if (!result)
		// NOTE: Raycast failed, return skybox color
		//
		return _config.skybox;

	Material &m = result.material;
	Vec3 normal = result.normal;
	Vec3 loc = result.hit_point;

	// NOTE: We need to add a slight bias to the shadow ray origin
	//		 in order to reduce surface acne.
	//
	Vec3 new_origin = loc - 0.001 * ray.dir;
	Color color{ 0.0 };

	for (const auto &light : scene.GetPointLights())
	{
		Vec3 light_dir = light.CalcDir(loc);

		if (glm::dot(normal, light_dir) <= 0.0)
			continue;

		color += light.CalcContribution(loc, -ray.dir, normal, m);
		
		Ray shadow_cast(new_origin, light_dir);
		HitResult shadow_hit = scene.RayCast(shadow_cast);

		if (shadow_hit && shadow_hit.distance < light.CalcDistance(loc))
			color *= shadow_hit.material.transmissivity;
	}

	for (const auto &light : scene.GetDirLights())
	{
		if (glm::dot(normal, -light.dir) <= 0.0)
			continue;

		color += light.CalcContribution(loc, -ray.dir, normal, m);
		
		Ray shadow_cast(new_origin, -light.dir);
		HitResult shadow_hit = scene.RayCast(shadow_cast);

		if (shadow_hit)
			color *= shadow_hit.material.transmissivity;
	}

	if (max_bounces == 0)
		return color;

	if (m.reflection > 0.0 && m.transmissivity < 1.0)
	{
		Ray reflected(new_origin, glm::reflect(ray.dir, normal));
		Color reflection = CalcColor(reflected, max_bounces - 1);
		color = glm::mix(color, reflection, m.reflection);
	}

	if (m.transmissivity > 0.0)
	{
		double dot = glm::dot(ray.dir, normal);
		Vec3 N = -normal;
		double eta = m.refractive_index;

		if (dot < 0.0)
		{
			// NOTE: We are entering this object
			eta = 1.0 / m.refractive_index;
			N = -N;
		}

		Vec3 ref_dir = glm::refract(ray.dir, N, eta);
		
		if (ref_dir == glm::zero<Vec3>())
			// NOTE: Total internal reflection!
			ref_dir = glm::reflect(ray.dir, normal);

		Ray refracted(loc + 0.001 * ray.dir, ref_dir);
		Color refraction = CalcColor(refracted, max_bounces - 1);
		color = glm::mix(color, refraction, m.transmissivity);
	}

	return color;
}

void RayTracer::Draw(ImageBuffer &image_buffer)
{
	auto extent = image_buffer.GetExtent();
	std::uint32_t width = extent.first;
	std::uint32_t height = extent.second;

	const Scene &scene = *_config.scene;
	const Camera &cam = scene.GetCameraConst();

	double distance = 1.0 / glm::tan(glm::radians(cam.GetFOV() / 2.0));
	Vec3 t = glm::normalize(cam.GetTarget() - cam.GetEye());
	Vec3 b, v;

	if (glm::abs(glm::dot(t, scene.GetWorldUp())) == glm::one<double>())
	{
		// NOTE: We are parallel to the world UP vector.
		//		 we need to use a different vector instead.
		//
		v = glm::normalize(glm::cross(t, scene.GetWorldRight()));
		b = glm::cross(v, t);
	}
	else
	{
		b = glm::normalize(glm::cross(t, scene.GetWorldUp()));
		v = glm::cross(t, b);
	}

	Vec3 qx = (2.0 / width) * b;
	Vec3 qy = (2.0 / height) * v;
	Vec3 bottom_left = t * distance - b - v;

	std::vector<std::thread> workers;
	workers.reserve(_config.thread_count);
		
	std::uint32_t total = width * height;
	std::uint32_t group_size = total / _config.thread_count;
	
	metrics.pixel_count = total;
	metrics.samples_per_pixel = _config.samples;

	for (int thread = 0; thread < _config.thread_count; ++thread)
	{
		workers.emplace_back(std::thread{ [=, &image_buffer]()
		{
			std::default_random_engine generator;
			std::uniform_real_distribution distribution;
			auto random = std::bind(distribution, generator);

			std::uint32_t start = thread * group_size;
			std::uint32_t end = start + glm::min(group_size, total - start);

			for (std::uint32_t i = start; i < end; ++i)
			{
				Color color{ 0.0 };

				for (int s = 0; s < _config.samples; ++s)
				{
					// TODO: Using uniform random distribution, may want to use blue noise for better effective
					//		 frequency.
					//
					double  x = (double)(i % width) + random() * 2.0 - 1.0;
					double  y = (double)(i / width) + random() * 2.0 - 1.0;

					Ray ray(cam.GetEye(), glm::normalize(bottom_left + qx * x + qy * y));
					color += CalcColor(ray, _config.ray_depth);
				}

				color /= _config.samples;

				image_buffer.WritePixel(i, color.r, color.g, color.b);
			}
		}});
	}

	for (auto& worker : workers)
		worker.join();
}
