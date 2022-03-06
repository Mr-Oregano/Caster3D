#pragma once

#include <glm/glm.hpp>

// Standard phong shading model.
//
struct Material
{
	glm::dvec3 color{ 1.0 };
	double reflection = 0.0;
};