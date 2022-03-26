
#include "Scene.h"

void Scene::AddMesh(const std::shared_ptr<Mesh> &mesh)
{
	_meshes.push_back(mesh);
}

void Scene::AddPointLight(const PointLight &light)
{
	_point_lights.push_back(light);
}

void Scene::AddDirLight(const DirectionalLight &light)
{
	_dir_lights.push_back(light);
}

HitResult Scene::RayCast(const Ray &ray, double max_distance)
{
	HitResult result;
	result.distance = max_distance;

	// NOTE: Traverse all triangle lists in scene and find the raycast hit with 
	//		 smallest distance.
	// 
	// TODO: Use bounding volume hierarchy to make this more efficient.
	//
	for (const auto &m : _meshes)
	{
		for (const Triangle &t : m->GetTriangleList())
		{
			Vec2 bari_center;
			double distance = max_distance;
			bool raycast_hit = glm::intersectRayTriangle(ray.origin, ray.dir, t.v0, t.v1, t.v2, bari_center, distance);

			if (raycast_hit && glm::zero<double>() < distance && distance < result.distance)
			{
				result.triangle = t;
				result.material = m->GetMaterial();
				result.distance = distance;
				result.hit_point = ray.GetPoint(distance);
				result.bari = Vec3{ bari_center, 1.0f - bari_center.x - bari_center.y };
				result.hit = true;
			}
		}
	}

	return result;
}