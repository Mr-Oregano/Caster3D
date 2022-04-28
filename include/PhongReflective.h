#pragma once

#include "Material.h"
#include "Phong.h"

struct PhongReflectiveConfig
{
	PhongConfig phong;

	double reflection = 0.0;
	double transmissivity = 0.0;
	double refractive_index = 1.0;
};

class PhongReflective : public Material
{
private:
	PhongReflectiveConfig _config;
	Phong _phong;

public:
	PhongReflective(const PhongReflectiveConfig config = {});
	virtual Color Shade(const ShadingContext &context, int samples, int max_depth) const override;
};
