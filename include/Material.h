#pragma once

#include <glm/glm.hpp>

// Standard phong shading model.
//
struct Material
{
	glm::vec3 color;
	float spec_strength = 1.0f;
	float amb_strength = 0.2f;
	float shininess = 32.0f;
};