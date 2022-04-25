#pragma once

#include "Maths.h"
#include "HitResult.h"

class Scene;

struct ShadingContext
{
	const Scene *scene = nullptr;
	HitResult hitInfo;
	Ray ray;
};

class Material
{
public:
	virtual ~Material() = default;
	virtual Color Shade(const ShadingContext &context, int samples, int max_depth) const = 0;
};