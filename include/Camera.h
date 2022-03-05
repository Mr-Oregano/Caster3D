#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera
{
private:
	glm::dvec3 _eye{ 0.0 };
	glm::dvec3 _target{ 0.0 };
	glm::dvec3 _up{ 0.0, 1.0, 0.0 };
	double _fov;

public:
	Camera(double fov);
	Camera(glm::dvec3 eye, glm::dvec3 target, double fov = 90.0f);

	void Translate(glm::dvec3 pos) { _eye = pos; }
	void LookAt(glm::dvec3 loc) { _target = loc; } 
	void SetFov(double fov) {  _fov = fov; }

	glm::dvec3 GetEye() const { return _eye; }
	glm::dvec3 GetTarget() const { return _target; }
	glm::dvec3 GetUp() const { return _up; }
	double GetFOV() const { return _fov; }
};