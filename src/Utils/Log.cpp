
#include "Log.h"

std::ostream &operator<<(std::ostream &os, const Vec3 &v)
{
	return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

std::ostream &operator<<(std::ostream &os, const PhongConfig &config)
{
	os << "Ambient: " << config.diffuse << std::endl
	   << "Diffuse: " << config.diffuse << std::endl
	   << "Specular: " << config.specular << std::endl
	   << "Shine: " << config.shine;

	if (config.ambient_tex)
		os << std::endl << "AmbientTex: " << config.ambient_sampling;

	if (config.diffuse_tex)
		os << std::endl << "DiffuseTex: " << config.diffuse_sampling;
	
	if (config.specular_tex)
		os << std::endl << "SpecularTex: " << config.specular_sampling;

	return os;
}

std::ostream &operator<<(std::ostream &os, const PhongReflectiveConfig &config)
{
	return os << config.phong << std::endl
			  << "IOR: " << config.refractive_index << std::endl
			  << "Reflection: " << config.reflection << std::endl
			  << "Transmissivity: " << config.transmissivity;
}

std::ostream &operator<<(std::ostream &os, TextureFilter type)
{
	switch (type)
	{
		case TextureFilter::LINEAR: return os << "LINEAR";
		case TextureFilter::NEAREST: return os << "NEAREST";
	}

	return os;
}

std::ostream &operator<<(std::ostream &os, TextureWrap type)
{
	switch (type)
	{
	case TextureWrap::REPEAT: return os << "REPEAT";
	case TextureWrap::CLAMP: return os << "CLAMP";
	case TextureWrap::MIRROR: return os << "MIRROR";
	}

	return os;
}

std::ostream &operator<<(std::ostream &os, TextureSampleParams params)
{
	return os << "(" << params.filter << " " << params.wrap << ")";
}
