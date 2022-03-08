#pragma once

#include "Scene.h"
#include "ImageBuffer.h"

#include <cstdint>
#include <memory>

class RayTracer
{
private:
	std::shared_ptr<Scene> _scene;

public:
	RayTracer(const std::shared_ptr<Scene> &scene);
	void Draw(ImageBuffer &image_buffer);

private:
	glm::dvec3 CalcColor(const Ray &ray, int max_bounces);
};