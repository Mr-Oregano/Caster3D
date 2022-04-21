#pragma once

#include "Maths.h"
#include "HitResult.h"
#include "AABB.h"

class Volume
{
public:
	virtual ~Volume() = default;

	virtual HitResult Hit(const Ray &ray) const = 0;
	virtual AABB GetAABB() const = 0;
};