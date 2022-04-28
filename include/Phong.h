#pragma once

#include "Material.h"
#include "Texture.h"

#include <memory>
#include <iostream>

struct PhongConfig
{
	Color specular{ 1.0 };
	Color diffuse{ 1.0 };
	Color ambient{ 0.0 };

	std::shared_ptr<Texture2D> ambient_tex;
	std::shared_ptr<Texture2D> diffuse_tex;
	std::shared_ptr<Texture2D> specular_tex;
	TextureSampleParams ambient_sampling;
	TextureSampleParams diffuse_sampling;
	TextureSampleParams specular_sampling;

	double shine = 32.0;
};

class Phong : public Material
{
private:
	PhongConfig _config;

public:
	Phong(const PhongConfig config = {});

	virtual Color Shade(const ShadingContext & context, int samples, int max_depth) const override;
};

