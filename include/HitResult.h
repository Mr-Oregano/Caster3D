#pragma once

#include "Maths.h"

class Material;

struct HitResult
{
	const Material *material = nullptr;
	Vec3 hit_point{ 0.0 };
	Vec3 normal{ 0.0 };
	Vec2 uv{ 0.0 };
	bool hit = false;
	double distance = 0.0;

	// NOTE: for debugging
	Color triangle_color;

public:
	operator bool() const { return hit; }
};