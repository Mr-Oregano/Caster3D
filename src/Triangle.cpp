
#include "Triangle.h"

#include <glm/gtx/intersect.hpp>

bool Triangle::Hit(Ray ray, HitResult &result) const
{
	result.material = material;
	result.normal = normal;
	glm::vec2 bari_center;

	result.hit = glm::intersectRayTriangle(
		ray.origin, ray.dir,
		v[0], v[1], v[2],
		bari_center,
		result.distance);

	result.hit_point = ray.GetPoint(result.distance);
	return result.hit;
}
