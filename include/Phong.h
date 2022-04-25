#pragma once

#include "Material.h"

struct PhongConfig
{
	Color specular{ 1.0 };
	Color diffuse{ 1.0 };
	Color ambient{ 0.0 };
	double shine = 32.0;
};

class Phong : public Material
{
private:
	PhongConfig _config;

public:
	Phong(const PhongConfig config = {});

	virtual Color Shade(const ShadingContext & context, int samples, int max_depth) const override;

	void SetConfig(PhongConfig config) { _config = config; }
};