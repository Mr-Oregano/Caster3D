
#include "Ray.h"

Ray::Ray(glm::vec3 start, glm::vec3 end)
	: origin(start), dir(glm::normalize(end - start))
{}

glm::vec3 Ray::GetPoint(float distance)
{
	return origin + distance * dir;
}
