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
	Vec3 hit_point{ 0.0 };
	Vec3 bari{ 0.0 };
	bool hit = false;
	double distance = 0.0;

public:
	operator bool() const { return hit; }
};

class Scene
{
private:
	std::vector<std::shared_ptr<Mesh>> _meshes;
	std::vector<PointLight> _point_lights;
	std::vector<DirectionalLight> _dir_lights;
	
	Camera _camera{ 90.0f };
	Vec3 _up{ 0.0, 1.0, 0.0 };
	Vec3 _right{ 1.0, 0.0, 0.0 };

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
	const Camera& GetCameraConst() const { return _camera; }
	Vec3 GetWorldUp() const { return _up; };
	Vec3 GetWorldRight() const { return _right; }
};