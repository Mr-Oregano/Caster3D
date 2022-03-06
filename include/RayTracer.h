#pragma once

#include "Scene.h"
#include "ImageBuffer.h"

#include <cstdint>
#include <memory>

struct HitResult
{
	Triangle triangle;
	Material material;
	glm::dvec3 hit_point{0.0};
	glm::dvec3 bari{0.0};
	bool hit = false;
	double distance = 0.0;

public:
	operator bool() const { return hit; }
};

class RayTracer
{
private:
	std::shared_ptr<Scene> _scene;

public:
	RayTracer(const std::shared_ptr<Scene> &scene);

	void Draw(ImageBuffer &image_buffer);

private:
	HitResult RayCast(const Ray &ray, double max_distance);
	glm::dvec3 CalcColor(const Ray &ray);
};