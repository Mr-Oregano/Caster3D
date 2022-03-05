#pragma once

#include <glm/glm.hpp>

// Standard phong shading model.
//
struct Material
{
	glm::dvec3 color{ 1.0 };
	double spec_strength = 1.0;
	double amb_strength = 0.2;
	double shininess = 32.0;
};