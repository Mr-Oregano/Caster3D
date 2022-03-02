#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera3D
{
private:
	glm::mat4 _view;
	glm::mat4 _proj;

public:
	Camera3D(float fov, float aspect);

	void MoveTo(glm::vec3 loc);
	void Rotate(glm::quat rot);

	glm::mat4 CalcViewProj();
};