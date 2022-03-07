#pragma once

#include <glm/glm.hpp>

#include "Material.h"

struct Ray
{
	glm::dvec3 origin{ 0.0 };
	glm::dvec3 dir{ 0.0, 1.0, 0.0 };

public:
	Ray() = default;
	Ray(glm::dvec3 origin, glm::dvec3 dir);

	glm::dvec3 GetPoint(double distance) const;
};