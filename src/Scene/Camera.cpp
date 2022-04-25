
#include "Camera.h"

#include <iostream>

Camera::Camera(double fov)
	: _fov(fov)
{}

Camera::Camera(Vec3 eye, Vec3 target, double fov)
	: _eye(eye), _target(target), _fov(fov)
{}
