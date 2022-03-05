
#include "Scene.h"

Scene::Scene(const std::initializer_list<std::shared_ptr<Mesh>> meshes, const std::initializer_list<Light> lights)
	: _meshes(meshes), _lights(lights)
{}

void Scene::AddMesh(const std::shared_ptr<Mesh> &mesh)
{
	_meshes.push_back(mesh);
}

void Scene::AddLight(const Light &light)
{
	_lights.push_back(light);
}
