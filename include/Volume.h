#pragma once

#include "Maths.h"
#include "HitResult.h"

class Volume
{
public:
	virtual ~Volume() = default;

	virtual HitResult Hit(const Ray &ray, double max_dsitance) const = 0;
};