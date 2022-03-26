#pragma once

#include "Maths.h"

struct Ray
{
	Vec3 origin{ 0.0 };
	Vec3 dir{ 0.0, 1.0, 0.0 };

public:
	Ray() = default;
	Ray(Vec3 origin, Vec3 dir);

	Vec3 GetPoint(double distance) const;
};