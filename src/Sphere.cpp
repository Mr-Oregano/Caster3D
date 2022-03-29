
#include "Sphere.h"

#include <iostream>

Sphere::Sphere(Vec3 center, double radius, const Material &material)
	: _center(center), _radius(radius), _material(material)
{}

HitResult Sphere::Hit(const Ray &ray, double max_distance) const
{
	HitResult result{};

	bool raycast_hit = glm::intersectRaySphere(ray.origin, ray.dir, _center, _radius * _radius, max_distance);

	if (raycast_hit && max_distance >= glm::zero<double>())
	{
		result.distance = max_distance;
		result.hit_point = ray.GetPoint(max_distance);
		result.normal = glm::normalize(result.hit_point - _center);
		result.material = _material;
		result.hit = true;
	}

	return result;
}
