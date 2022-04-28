
#include "Phong.h"

#include "Scene.h"

Phong::Phong(const PhongConfig config)
	: _config(config)
{}

Color Phong::Shade(const ShadingContext &context, int samples, int _) const
{
	Color color{ 0.0 };
	const Scene &scene = *context.scene;
	const HitResult &info = context.hitInfo;

	const Vec3 &normal = info.normal;
	const Vec3 &loc = info.hit_point;
	const Ray &ray = context.ray;

	// NOTE: We need to add a slight bias to the shadow ray origin
	//		 in order to reduce surface acne.
	//
	Vec3 new_origin = loc - 0.001 * ray.dir;

	Color ambient_col = _config.ambient;
	Color diffuse_col = _config.diffuse;
	Color specular_col = _config.specular;

	if (_config.ambient_tex)
		ambient_col *= _config.ambient_tex->Sample(info.uv, _config.ambient_sampling);

	if (_config.diffuse_tex)
		diffuse_col *= _config.diffuse_tex->Sample(info.uv, _config.diffuse_sampling);

	if (_config.specular_tex)
		specular_col *= _config.specular_tex->Sample(info.uv, _config.specular_sampling);

	// TODO: Need to account for semi-transparent objects that could change the color
	//		 of shadow
	//
	for (const auto &light : scene.GetPointLights())
	{
		double light_dist = glm::distance(loc, light.pos);
		Vec3 light_dir = glm::normalize(light.pos - loc);
		color += light.ambient * ambient_col;

		if (glm::dot(normal, light_dir) <= 0.0)
			continue;

		Ray shadow_cast(new_origin, light_dir);
		HitResult shadow_hit = scene.RayCast(shadow_cast);

		if (shadow_hit && shadow_hit.distance < light_dist)
			continue;

		Vec3 light_reflected = glm::reflect(light_dir, normal);

		double light_contribution = glm::dot(normal, light_dir);
		double diffuse = glm::max(light_contribution, 0.0);
		double specular = glm::max(glm::dot(-ray.dir, light_reflected), 0.0);
		double attenuation = light.brightness / (1.0 + light_dist * light_dist);

		Color output = glm::pow(specular, _config.shine) * specular_col + diffuse * diffuse_col;
		color += light.color * output * attenuation;
	}

	for (const auto &light : scene.GetDirLights())
	{
		double light_contribution = glm::dot(normal, -light.dir);
		color += light.ambient * ambient_col;

		if (light_contribution <= 0.0)
			continue;

		Ray shadow_cast(new_origin, -light.dir);
		HitResult shadow_hit = scene.RayCast(shadow_cast);

		if (shadow_hit)
			continue;

		Vec3 light_reflected = glm::reflect(-light.dir, normal);

		double diffuse = light_contribution;
		double specular = glm::max(glm::dot(-ray.dir, light_reflected), 0.0);

		Color output = glm::pow(specular, _config.shine) * specular_col + diffuse * diffuse_col;
		color += light.color * output;
	}

	return color;
}


