#pragma once

#include "Ray.h"
#include "Material.h"

#include <glm/glm.hpp>

struct Triangle
{
	union 
	{
		struct { Vec3 v0, v1, v2; };
		Vec3 v[3];
	};
	
	Vec3 normal{ 1.0f };
	Color color{ 1.0f };
};