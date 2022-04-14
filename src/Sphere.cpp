
#include "Sphere.h"

#include <iostream>

Sphere::Sphere(Vec3 center, double radius, const Material &material)
	: _center(center), _radius(radius), _material(material)
{}

HitResult Sphere::Hit(const Ray &ray) const
{
	HitResult result{};

	double distance = 0.0;
	bool raycast_hit = glm::intersectRaySphere(ray.origin, ray.dir, _center, _radius * _radius, distance);

	if (raycast_hit && distance >= glm::zero<double>())
	{
		result.distance = distance;
		result.hit_point = ray.GetPoint(result.distance);
		result.normal = glm::normalize(result.hit_point - _center);
		result.material = _material;
		result.hit = true;
	}

	return result;
}
