
#include "Triangle.h"

#include <string>
#include <iostream>

Triangle::Triangle(Vec3 v[3], Vec3 n[3], const Material *material)
	: _material(material)
{
	std::memcpy(_v, v, sizeof(Vec3) * 3);
	std::memcpy(_n, n, sizeof(Vec3) * 3);
}

Triangle::Triangle(Vec3 v[3], Vec3 n[3], Color color, const Material *material)
	: Triangle(v, n, material)
{
	_color = color;
}

HitResult Triangle::Hit(const Ray &ray) const
{
	HitResult result{};
	
	Vec2 bari;

	double distance = 0.0;
	bool raycast_hit = glm::intersectRayTriangle(ray.origin, ray.dir, _v[0], _v[1], _v[2], bari, distance);

	if (raycast_hit && distance >= glm::zero<double>())
	{
		Vec3 interpolate{ bari, 1.0f - bari.x - bari.y };
		
		// No idea why it's done in this order (z -> v0, x -> v1, y -> v2) glm has no documentation
		// for this crap.

		result.normal = interpolate.z * _n[0] + interpolate.x * _n[1] + interpolate.y * _n[2];
		result.material = *_material;
		result.material.diffuse *= _color;

		result.distance = distance;
		result.hit_point = ray.GetPoint(result.distance);
		result.hit = true;
	}

	return result;
}

void Triangle::Transform(const Mat4 &model, const Mat3 &norm)
{
	for (int i = 0; i < 3; ++i)
	{
		Vec4 v{ _v[i], 1.0f };
		_v[i] = Vec3{ model * v };
		_n[i] = glm::normalize(norm * _n[i]);
	}
}
