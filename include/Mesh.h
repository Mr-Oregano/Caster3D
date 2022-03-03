#pragma once

#include <Triangle.h>

#include <glm/glm.hpp>

class Mesh
{
public:
	Triangle *_triangles;
	std::size_t _count;

public:
	Mesh(Triangle _primitives[], std::size_t count);
	virtual ~Mesh() = default;

	void Transform(const glm::mat4 &model);
};

