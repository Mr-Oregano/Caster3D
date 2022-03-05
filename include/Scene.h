#pragma once

#include "Light.h"
#include "Mesh.h"
#include "Camera.h"

#include <vector>
#include <memory>

class Scene
{
private:
	std::vector<std::shared_ptr<Mesh>> _meshes;
	std::vector<Light> _lights;
	Camera _camera{ 90.0f };

public:
	Scene() = default;
	Scene(const std::initializer_list<std::shared_ptr<Mesh>> meshes, const std::initializer_list<Light> lights);

	void AddMesh(const std::shared_ptr<Mesh> &mesh);
	void AddLight(const Light &light);

	const auto& GetLights() const { return _lights; }
	const auto& GetMeshes() const { return _meshes; }
	Camera& GetCamera() { return _camera; }
};