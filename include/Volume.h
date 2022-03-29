#pragma once

#include "Maths.h"
#include "HitResult.h"

class Volume
{
public:
	virtual HitResult Hit(const Ray &ray, double max_dsitance) const = 0;
};