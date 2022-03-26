#pragma once

#include "Scene.h"
#include "ImageBuffer.h"
#include "Maths.h"

#include <cstdint>
#include <memory>

class RayTracer
{
private:
	std::shared_ptr<Scene> _scene;

public:
	RayTracer(const std::shared_ptr<Scene> &scene);
	void Draw(ImageBuffer &image_buffer, int samples = 1);

private:
	Color CalcColor(const Ray &ray, int max_bounces);
};