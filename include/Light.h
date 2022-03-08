#pragma once

#include "Material.h"

#include <glm/glm.hpp>

struct PointLight
{
	glm::dvec3 pos;
	glm::dvec3 color;
	double brightness;

public:
	PointLight(glm::dvec3 pos, glm::dvec3 color, double brightness = 1.0);

	glm::dvec3 CalcContribution(glm::dvec3 loc, glm::dvec3 view, glm::dvec3 normal, const Material &m) const;
	glm::dvec3 CalcDir(glm::dvec3 loc) const;
	double CalcDistance(glm::dvec3 loc) const;
};

struct DirectionalLight
{
	glm::dvec3 dir;
	glm::dvec3 color;

public:
	DirectionalLight(glm::dvec3 dir, glm::dvec3 color);

	glm::dvec3 CalcContribution(glm::dvec3 loc, glm::dvec3 view, glm::dvec3 normal, const Material &m) const;
};