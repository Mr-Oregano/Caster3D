#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera3D
{
private:
	glm::vec3 _eye;
	glm::vec3 _lookAt;

public:
	Camera3D(glm::vec3 eye, glm::vec3 target);

	glm::vec3 GetEye() const { return _eye; }
	glm::vec3 GetTarget() const { return _lookAt; }
};