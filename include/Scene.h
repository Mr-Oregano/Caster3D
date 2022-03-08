#pragma once

#include "Light.h"
#include "Mesh.h"
#include "Camera.h"

#include <vector>
#include <memory>

struct HitResult
{
	Triangle triangle;
	Material material;
	glm::dvec3 hit_point{ 0.0 };
	glm::dvec3 bari{ 0.0 };
	bool hit = false;
	double distance = 0.0;

public:
	operator bool() const { return hit; }
};

struct LightResult
{
	glm::dvec3 ambient;
	glm::dvec3 specular;
};

class Scene
{
private:
	std::vector<std::shared_ptr<Mesh>> _meshes;
	std::vector<PointLight> _point_lights;
	std::vector<DirectionalLight> _dir_lights;
	Camera _camera{ 90.0f };

public:
	Scene() = default;

	void AddMesh(const std::shared_ptr<Mesh> &mesh);
	void AddPointLight(const PointLight &light);
	void AddDirLight(const DirectionalLight &light);

	HitResult RayCast(const Ray &ray, double max_distance);

	const auto& GetPointLights() const { return _point_lights; }
	const auto& GetDirLights() const { return _dir_lights; }
	const auto& GetMeshes() const { return _meshes; }
	Camera& GetCamera() { return _camera; }
};