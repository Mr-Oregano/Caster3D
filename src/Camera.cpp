
#include "Camera.h"

Camera3D::Camera3D(glm::vec3 eye, glm::vec3 target)
	: _eye(eye), _lookAt(target)
{}
