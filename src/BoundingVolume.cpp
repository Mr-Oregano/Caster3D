
#include "BoundingVolume.h"

#include <algorithm>

BoundingVolume::BoundingVolume(Volume *left, Volume *right)
{
	_children[0] = left;
	_children[1] = right;

	AABB laabb = left->GetAABB();
	AABB raabb = right->GetAABB();

	_aabb.bl.x = glm::min(laabb.bl.x, raabb.bl.x);
	_aabb.bl.y = glm::min(laabb.bl.y, raabb.bl.y);
	_aabb.bl.z = glm::min(laabb.bl.z, raabb.bl.z);

	_aabb.tr.x = glm::max(laabb.tr.x, raabb.tr.x);
	_aabb.tr.y = glm::max(laabb.tr.y, raabb.tr.y);
	_aabb.tr.z = glm::max(laabb.tr.z, raabb.tr.z);
}

HitResult BoundingVolume::Hit(const Ray &ray) const
{
	Vec3 t1 = (_aabb.bl - ray.origin) / ray.dir;
	Vec3 t2 = (_aabb.tr - ray.origin) / ray.dir;

	if (t2.x < t1.x)
		std::swap(t1.x, t2.x);

	if (t2.y < t1.y)
		std::swap(t1.y, t2.y);

	if (t2.z < t1.z)
		std::swap(t1.z, t2.z);

	double start = glm::max(t1.x, glm::max(t1.y, t1.z));
	double end = glm::min(t2.x, glm::min(t2.y, t2.z));

	++metrics.avg_hit_tests_per_raycast;

	if (start <= end && end >= glm::zero<double>())
	{
		HitResult result;
		result.distance = std::numeric_limits<double>::infinity();

		for (const Volume *v : _children)
		{
			HitResult v_hit = v->Hit(ray);

			if (v_hit && v_hit.distance < result.distance)
				result = std::move(v_hit);
		}

		return result;
	}

	return {};
}

AABB BoundingVolume::GetAABB() const
{
	return _aabb;
}
