#pragma once

#include "Light.h"
#include "Camera.h"
#include "HitResult.h"
#include "Volume.h"

#include "Sphere.h"
#include "Triangle.h"
#include "BoundingVolume.h"
#include "Metrics.h"

#include <vector>
#include <memory>
#include <string>

class Scene
{
private:
	const Volume *_root = nullptr;

	// NOTE: We reference volumes and resources by their interfaces, but
	//		 we still need to store their values somewhere. 
	//
	std::vector<Sphere> _spheres;
	std::vector<Triangle> _triangles;
	std::vector<BoundingVolume> _bounds;

	std::vector<Material> _materials;
	std::vector<PointLight> _point_lights;
	std::vector<DirectionalLight> _dir_lights;
	
	Camera _camera{ 90.0f };
	Vec3 _up{ 0.0, 1.0, 0.0 };
	Vec3 _right{ 1.0, 0.0, 0.0 };
	
	bool _built = false;
	bool _loaded = false;

public:
	Scene(const std::string &filename, const std::string &material_path);
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	void AddPointLight(const PointLight &light);
	void AddDirLight(const DirectionalLight &light);
	void Build();

	HitResult RayCast(const Ray &ray);

	const auto& GetPointLights() const { return _point_lights; }
	const auto& GetDirLights() const { return _dir_lights; }
	
	Camera& GetCamera() { return _camera; }
	const Camera& GetCameraConst() const { return _camera; }
	Vec3 GetWorldUp() const { return _up; };
	Vec3 GetWorldRight() const { return _right; }

private:
	Volume *SplitBVH(std::size_t left, std::size_t right);

};