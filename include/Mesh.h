#pragma once

#include <glm/glm.hpp>

struct Triangle
{
	glm::vec3 v[3];
	glm::vec3 normal;
};

struct Mesh
{
	Triangle *_primitives;
	std::size_t _size;
};