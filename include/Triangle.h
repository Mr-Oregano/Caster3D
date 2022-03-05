#pragma once

#include "Ray.h"
#include "Material.h"

#include <glm/glm.hpp>

struct Triangle
{
	union 
	{
		struct { glm::dvec3 v0, v1, v2; };
		glm::dvec3 v[3];
	};
	
	glm::dvec3 normal{ 1.0f };
	glm::dvec3 color{ 1.0f };
};