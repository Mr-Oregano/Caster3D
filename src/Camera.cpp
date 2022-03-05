
#include "Camera.h"

#include <iostream>

Camera::Camera(double fov)
	: _fov(fov)
{}

Camera::Camera(glm::dvec3 eye, glm::dvec3 target, double fov)
	: _eye(eye), _target(target), _fov(fov)
{}
