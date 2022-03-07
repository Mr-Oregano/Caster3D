
#include "Ray.h"

Ray::Ray(glm::dvec3 origin, glm::dvec3 dir)
	: origin(origin), dir(dir)
{}

glm::dvec3 Ray::GetPoint(double distance) const
{
	return origin + distance * dir;
}
