#pragma once

#include <glm/glm.hpp>

#include "Material.h"

struct Ray
{
	glm::vec3 origin{0.0f};
	glm::vec3 dir{1.0f};

public:
	Ray() = default;
	Ray(glm::vec3 start, glm::vec3 end);

	glm::vec3 GetPoint(float distance);
};

struct HitResult
{
	Material material;
	glm::vec3 normal;
	glm::vec3 hit_point;
	bool hit = false;
	float distance = 0.0f;
};