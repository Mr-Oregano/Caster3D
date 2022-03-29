#pragma once

#include "Material.h"
#include "Volume.h"
#include "Maths.h"

class Triangle : public Volume
{
private:
	Vec3 _normal{ 1.0f };
	const Material *_material = nullptr;
	Vec3 _v[3]{};
	Color _color{ 1.0f };

public:
	Triangle(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 normal, const Material *material);
	Triangle(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 normal, Color color, const Material *material);

	virtual HitResult Hit(const Ray &ray, double max_distance) const override;

	// NOTE: computing the normal matrix is expensive considering
	//		 this triangle may be part of a massive model, so we
	//		 make the caller create the normal matrix.
	//
	void Transform(const Mat4 &model, const Mat3 &norm);
};