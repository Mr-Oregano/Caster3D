#pragma once

#include "Maths.h"
#include "Material.h"

struct HitResult
{
	Material material;
	Vec3 hit_point{ 0.0 };
	Vec3 normal{ 0.0 };
	bool hit = false;
	double distance = 0.0;

public:
	operator bool() const { return hit; }
};