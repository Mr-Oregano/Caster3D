
#include "PhongReflective.h"

#include "Scene.h"

PhongReflective::PhongReflective(const PhongReflectiveConfig config)
	: _config(config)
{
	// NOTE: We create our own Phong material that we will shade.
	//		 PhongReflective is an extension on phong.
	//
	_phong = { config.phong };
}

Color PhongReflective::Shade(const ShadingContext &context, int samples, int max_depth) const
{
	// NOTE: Calculate phong.
	Color color = _phong.Shade(context, samples, max_depth);

	if (max_depth == 0)
		return color;

	const Scene &scene = *context.scene;
	const HitResult &info = context.hitInfo;

	const Vec3 &normal = info.normal;
	const Vec3 &loc = info.hit_point;
	const Ray &ray = context.ray;

	Color reflection_col = Color{ _config.reflection };

	if (_config.phong.specular_tex)
		reflection_col *= _config.phong.specular_tex->Sample(info.uv, _config.phong.specular_sampling);

	if (glm::length2(reflection_col) > 0 && _config.transmissivity < 1.0)
	{
		// NOTE: We need to add a slight bias to the ray origin in 
		//		 order to reduce surface acne.
		//
		Vec3 new_origin = loc - 0.001 * ray.dir;
		Ray reflected(new_origin, glm::reflect(ray.dir, normal));
		Color reflection = scene.Trace(reflected, samples, max_depth - 1);

		color = glm::mix(color, reflection * reflection_col, _config.reflection);
	}

	if (_config.transmissivity > 0.0)
	{
		double dot = glm::dot(ray.dir, normal);
		Vec3 N = -normal;
		double eta = _config.refractive_index;

		if (dot < 0.0)
		{
			// NOTE: We are entering this object
			eta = 1.0 / _config.refractive_index;
			N = -N;
		}

		Vec3 ref_dir = glm::refract(ray.dir, N, eta);

		if (ref_dir == glm::zero<Vec3>())
			// NOTE: Total internal reflection!
			ref_dir = glm::reflect(ray.dir, normal);

		// NOTE: We need to add a slight bias to the ray origin in 
		//		 order to reduce surface acne.
		//
		Vec3 new_origin = loc + 0.001 * ray.dir;
		Ray refracted(new_origin, ref_dir);
		Color refraction = scene.Trace(refracted, samples, max_depth - 1);
		color = glm::mix(color, refraction, _config.transmissivity);
	}

	return color;
}
