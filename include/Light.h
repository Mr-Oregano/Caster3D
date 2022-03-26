#pragma once

#include "Material.h"

#include "Maths.h"

struct PointLight
{
	Vec3 pos;
	Color color;
	double brightness;

public:
	PointLight(Vec3 pos, Color color, double brightness = 1.0);

	Color CalcContribution(Vec3 loc, Vec3 view, Vec3 normal, const Material &m) const;
	Vec3 CalcDir(Vec3 loc) const;
	double CalcDistance(Vec3 loc) const;
};

struct DirectionalLight
{
	Vec3 dir;
	Color color;

public:
	DirectionalLight(Vec3 dir, Color color);

	Color CalcContribution(Vec3 loc, Vec3 view, Vec3 normal, const Material &m) const;
};