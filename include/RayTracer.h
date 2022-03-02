#pragma once

#include "Light.h"
#include "Camera.h"
#include "Mesh.h"

#include <cstdint>

class RayTracer
{
public:
	RayTracer(Light light[], Camera3D *camera, Mesh *mesh);

	// NOTE: Destination assumes RGB_8 format 
	//
	void Draw(int width, int height, std::uint8_t *destination);
};