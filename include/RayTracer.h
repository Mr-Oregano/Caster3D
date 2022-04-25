#pragma once

#include "Scene.h"
#include "ImageBuffer.h"
#include "Maths.h"

#include <cstdint>
#include <memory>

struct RayTracerConfig
{
	std::uint8_t samples = 10;
	std::uint8_t ray_depth = 8;
	std::uint8_t thread_count = 32;
};

class RayTracer
{
private:
	RayTracerConfig _config;

public:
	RayTracer(const RayTracerConfig &config);
	void Draw(Scene &scene, ImageBuffer &image_buffer);

};