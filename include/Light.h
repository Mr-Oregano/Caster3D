#pragma once

#include "Material.h"

#include "Maths.h"

struct PointLight
{
	Vec3 pos;
	Color color;
	double brightness;
	double ambient;

public:
	PointLight(Vec3 pos, Color color, double brightness = 1.0, double ambient = 0.25);

	Color CalcContribution(Vec3 loc, Vec3 view, Vec3 normal, const Material &m) const;
	Vec3 CalcDir(Vec3 loc) const;
	double CalcDistance(Vec3 loc) const;
};

struct DirectionalLight
{
	Vec3 dir;
	Color color;
	double ambient;

public:
	DirectionalLight(Vec3 dir, Color color, double ambient = 0.25);

	Color CalcContribution(Vec3 loc, Vec3 view, Vec3 normal, const Material &m) const;
};