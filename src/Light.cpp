
#include "Light.h"

PointLight::PointLight(Vec3 pos, Color color, double brightness)
	: pos(pos), color(color), brightness(brightness)
{}

Color PointLight::CalcContribution(Vec3 loc, Vec3 view, Vec3 normal, const Material &m) const
{
	double light_dist = CalcDistance(loc);
	Vec3 light_dir = CalcDir(loc);
	Vec3 light_reflected = glm::reflect(light_dir, normal);

	double light_contribution = glm::dot(normal, light_dir);
	double diffuse = glm::max(light_contribution, 0.0);
	double specular = glm::max(glm::dot(view, light_reflected), 0.0);
	double attenuation = brightness / (1.0 + light_dist * light_dist);

	double output = diffuse * m.diffuse + glm::pow(specular, m.shine) * m.specular;
	return color * output * attenuation;
}

Vec3 PointLight::CalcDir(Vec3 loc) const
{
	return glm::normalize(pos - loc);
}

double PointLight::CalcDistance(Vec3 loc) const
{
	return glm::distance(loc, pos);
}

DirectionalLight::DirectionalLight(Vec3 dir, Color color)
	: dir(glm::normalize(dir)), color(color)
{}

Color DirectionalLight::CalcContribution(Vec3 loc, Vec3 view, Vec3 normal, const Material &m) const
{
	Vec3 light_reflected = glm::reflect(-dir, normal);
	double light_contribution = glm::dot(normal, -dir);

	double diffuse = glm::max(light_contribution, 0.0);
	double specular = glm::max(glm::dot(view, light_reflected), 0.0);

	double output = diffuse * m.diffuse + glm::pow(specular, m.shine) * m.specular;
	return color * output;
}
