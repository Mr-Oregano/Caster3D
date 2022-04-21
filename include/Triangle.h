#pragma once

#include "Material.h"
#include "Volume.h"
#include "Maths.h"

class Triangle : public Volume
{
private:
	Vec3 _v[3]{};
	Vec3 _n[3]{};
	Color _color{ 1.0f };
	AABB _aabb;
	const Material *_material = nullptr;

public:
	Triangle(Vec3 v[3], Vec3 n[3], const Material *material);
	Triangle(Vec3 v[3], Vec3 n[3], Color color, const Material *material);

	virtual HitResult Hit(const Ray &ray) const override;
	virtual AABB GetAABB() const override;

	// NOTE: computing the normal matrix is expensive considering
	//		 this triangle may be part of a massive model, so we
	//		 make the caller create the normal matrix.
	//
	void Transform(const Mat4 &model, const Mat3 &norm);
};