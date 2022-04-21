#pragma once

#include "Volume.h"

class BoundingVolume : public Volume
{
private:
	AABB _aabb;
	Volume *_children[2];

public:
	BoundingVolume(Volume *left, Volume *right);

	virtual HitResult Hit(const Ray & ray) const override;
	virtual AABB GetAABB() const override;
};