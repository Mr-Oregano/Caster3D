#pragma once

#include <glm/glm.hpp>

struct Light
{
	glm::vec3 pos;
	glm::vec3 color;

public:
	Light() = default;
	Light(glm::vec3 pos, glm::vec3 color);
};