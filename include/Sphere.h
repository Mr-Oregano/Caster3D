#pragma once

#include "Volume.h"
#include "Material.h"

class Sphere : public Volume
{
private:
	Vec3 _center;
	double _radius;
	const Material *_material;

public:
	Sphere(Vec3 center, double radius, const Material *material);

	virtual HitResult Hit(const Ray &ray) const override;
	virtual AABB GetAABB() const override;
};