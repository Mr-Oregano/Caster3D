#pragma once

#include "Light.h"
#include "Camera.h"
#include "Mesh.h"

class RayTracer
{
public:
	RayTracer(Light light[], Camera3D *camera, Mesh *mesh);
};