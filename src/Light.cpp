
#include "Light.h"

#include <glm/ext.hpp>

PointLight::PointLight(glm::dvec3 pos, glm::dvec3 color, double brightness)
	: pos(pos), color(color), brightness(brightness)
{}

glm::dvec3 PointLight::CalcContribution(glm::dvec3 loc, glm::dvec3 view, glm::dvec3 normal, const Material &m) const
{
	double light_dist = CalcDistance(loc);
	glm::dvec3 light_dir = CalcDir(loc);
	glm::dvec3 light_reflected = glm::reflect(light_dir, normal);

	double light_contribution = glm::dot(normal, light_dir);
	double diffuse = glm::max(light_contribution, 0.0);
	double specular = glm::max(glm::dot(view, light_reflected), 0.0);
	double attenuation = brightness / (1.0 + light_dist * light_dist);

	double output = diffuse * m.diffuse + glm::pow(specular, m.shine) * m.specular;
	return color * output * attenuation;
}

glm::dvec3 PointLight::CalcDir(glm::dvec3 loc) const
{
	return glm::normalize(pos - loc);
}

double PointLight::CalcDistance(glm::dvec3 loc) const
{
	return glm::distance(loc, pos);
}

DirectionalLight::DirectionalLight(glm::dvec3 dir, glm::dvec3 color)
	: dir(glm::normalize(dir)), color(color)
{}

glm::dvec3 DirectionalLight::CalcContribution(glm::dvec3 loc, glm::dvec3 view, glm::dvec3 normal, const Material &m) const
{
	glm::dvec3 light_reflected = glm::reflect(-dir, normal);
	double light_contribution = glm::dot(normal, -dir);

	double diffuse = glm::max(light_contribution, 0.0);
	double specular = glm::max(glm::dot(view, light_reflected), 0.0);

	double output = diffuse * m.diffuse + glm::pow(specular, m.shine) * m.specular;
	return color * output;
}
