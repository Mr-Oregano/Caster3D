#pragma once

#include "Material.h"

#include "Maths.h"

struct PointLight
{
	Vec3 pos;
	Color color;
	double brightness;
	double ambient;
};

struct DirectionalLight
{
	Vec3 dir;
	Color color;
	double ambient;
};