
#include "Triangle.h"

Triangle::Triangle(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 normal, const Material *material)
	: _normal(normal), _material(material)
{
	_v[0] = v0;
	_v[1] = v1;
	_v[2] = v2;
}

Triangle::Triangle(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 normal, Color color, const Material *material)
	: Triangle(v0, v1, v2, normal, material)
{
	_color = color;
}

HitResult Triangle::Hit(const Ray &ray, double max_distance) const
{
	HitResult result{};
	
	Vec2 bari;
	bool raycast_hit = glm::intersectRayTriangle(ray.origin, ray.dir, _v[0], _v[1], _v[2], bari, max_distance);

	if (raycast_hit && max_distance >= glm::zero<double>())
	{
		// TODO: Interpolate normal and color values
		// Vec3 interpolate{ bari, 1.0f - bari.x - bari.y };
		//
		result.normal = _normal;
		result.material = *_material;
		result.material.color *= _color;

		result.distance = max_distance;
		result.hit_point = ray.GetPoint(max_distance);
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
	}

	_normal = glm::normalize(norm * _normal);
}
