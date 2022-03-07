#pragma once

#include <glm/glm.hpp>

struct Light
{
	glm::dvec3 pos;
	glm::dvec3 color;
	double brightness;

public:
	Light() = default;
	Light(glm::dvec3 pos, glm::dvec3 color, double brightness = 1.0);
};