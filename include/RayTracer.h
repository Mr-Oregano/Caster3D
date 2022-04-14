#pragma once

#include "Scene.h"
#include "ImageBuffer.h"
#include "Maths.h"

#include <cstdint>
#include <memory>

struct RayTracerConfig
{
	std::shared_ptr<Scene> scene;
	std::uint8_t samples = 1;
	std::uint8_t ray_depth = 8;
	Color skybox{ 0.0 };
};

class RayTracer
{
private:
	RayTracerConfig _config;

public:
	RayTracer(const RayTracerConfig &config);
	void Draw(ImageBuffer &image_buffer);

private:
	Color CalcColor(const Ray &ray, int max_bounces);

};