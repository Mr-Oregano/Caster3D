
#include "Scene.h"

#include <algorithm>

void Scene::AddMesh(const MeshPtr &mesh)
{
	assert(!_built);

	_meshes.push_back(mesh);
}

void Scene::AddSphere(const Sphere &sphere)
{
	assert(!_built);

	_spheres.push_back(sphere);
	_volumes.push_back(static_cast<const Volume*>(&*(_spheres.end() - 1)));
}

void Scene::AddPointLight(const PointLight &light)
{
	assert(!_built);

	_point_lights.push_back(light);
}

void Scene::AddDirLight(const DirectionalLight &light)
{
	assert(!_built);

	_dir_lights.push_back(light);
}

void Scene::Build()
{
	assert(!_built);

	// TODO: Build bounding volume hierarchy to make raycasts more efficient.

	for (const auto &mesh : _meshes)
	{
		std::size_t count = mesh->GetTriangleCount();
		const auto& triangles = mesh->GetTriangleList();

		_volumes.reserve(_volumes.size() + count);

		for (int i = 0; i < count; ++i)
			_volumes.push_back(static_cast<const Volume*>(&triangles[i]));
	}

	_built = true;
}

HitResult Scene::RayCast(const Ray &ray, double max_distance)
{
	// NOTE: The scene must have been built before we can raycast
	assert(_built);

	HitResult result;
	result.distance = max_distance;

	for (const Volume *v : _volumes)
	{
		HitResult v_hit = v->Hit(ray, max_distance);
		
		// NOTE: Traverse all triangle lists in scene and find the raycast hit with 
		//		 smallest distance.
		// 
		if (v_hit && v_hit.distance < result.distance)
			result = std::move(v_hit);
	}

	return result;
}