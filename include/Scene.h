#pragma once

#include "Light.h"
#include "Camera.h"
#include "HitResult.h"
#include "Volume.h"

#include "Sphere.h"
#include "Mesh.h"

#include <vector>
#include <memory>

class Scene
{
private:
	using MeshPtr = std::shared_ptr<const Mesh>;

	std::vector<const Volume*> _volumes;
	
	// NOTE: We care about volumes but some may need to be stored
	//		 by the scene so we can maintain ownership.
	//
	std::vector<Sphere> _spheres;
	std::vector<MeshPtr> _meshes;

	std::vector<PointLight> _point_lights;
	std::vector<DirectionalLight> _dir_lights;
	
	Camera _camera{ 90.0f };
	Vec3 _up{ 0.0, 1.0, 0.0 };
	Vec3 _right{ 1.0, 0.0, 0.0 };
	
	bool _built = false;

public:
	Scene() = default;
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	void AddMesh(const MeshPtr &mesh);
	void AddSphere(const Sphere &sphere);

	void AddPointLight(const PointLight &light);
	void AddDirLight(const DirectionalLight &light);
	void Build();

	HitResult RayCast(const Ray &ray, double max_distance);

	const auto& GetPointLights() const { return _point_lights; }
	const auto& GetDirLights() const { return _dir_lights; }
	
	Camera& GetCamera() { return _camera; }
	const Camera& GetCameraConst() const { return _camera; }
	Vec3 GetWorldUp() const { return _up; };
	Vec3 GetWorldRight() const { return _right; }
};