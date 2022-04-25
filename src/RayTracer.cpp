
#include "RayTracer.h"
#include "Metrics.h"

#include <iostream>
#include <random>
#include <functional>
#include <thread>

RayTracer::RayTracer(const RayTracerConfig &config)
	: _config(config)
{}

void RayTracer::Draw(Scene &scene, ImageBuffer &image_buffer)
{
	auto [ width, height ] = image_buffer.GetExtent();

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
	Vec3 eye = cam.GetEye();
		
	std::uint32_t total = width * height;
	
	metrics.pixel_count = total;
	metrics.samples_per_pixel = _config.samples;

	std::uint32_t group_size = total / _config.thread_count;
	std::vector<std::thread> workers;
	workers.reserve(_config.thread_count);

	for (int thread = 0; thread < _config.thread_count; ++thread)
	{
		workers.emplace_back(std::thread{ [=, &image_buffer, &scene]()
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

					Ray ray(eye, glm::normalize(bottom_left + qx * x + qy * y));
					color += scene.Trace(ray, _config.samples, _config.ray_depth);
				}

				color /= _config.samples;

				image_buffer.WritePixel(i, color.r, color.g, color.b);
			}
		} });
	}

	for (auto &worker : workers)
		worker.join();
}
