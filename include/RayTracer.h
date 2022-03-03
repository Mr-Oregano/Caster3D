#pragma once

#include "Light.h"
#include "Camera.h"
#include "Mesh.h"

#include "ImageBuffer.h"

#include <cstdint>

class RayTracer
{
private:
	Camera3D *_camera = nullptr;
	Mesh *_mesh = nullptr;
	Light *_light = nullptr;

public:
	RayTracer(Light *light, Camera3D *camera, Mesh *mesh);

	// NOTE: Destination assumes RGB_8 format 
	//
	void Draw(ImageBuffer &target);

private:
	glm::vec3 CastRay(const Ray &ray, Triangle triangles[], std::size_t triangles_count);
};