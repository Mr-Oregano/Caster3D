
#include "Ray.h"

Ray::Ray(glm::dvec3 start, glm::dvec3 end)
	: origin(start), dir(glm::normalize(end - start))
{}

glm::dvec3 Ray::GetPoint(double distance) const
{
	return origin + distance * dir;
}
