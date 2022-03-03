#pragma once

#include "Ray.h"
#include "Material.h"

#include <glm/glm.hpp>

struct Triangle
{
	glm::vec3 v[3];
	glm::vec3 normal;
	Material material;

public:
	bool Hit(Ray ray, HitResult &result) const;
};