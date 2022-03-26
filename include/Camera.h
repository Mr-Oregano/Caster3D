#pragma once

#include "Maths.h"

class Camera
{
private:
	Vec3 _eye{ 0.0 };
	Vec3 _target{ 0.0 };
	Vec3 _up{ 0.0, 1.0, 0.0 };
	double _fov;

public:
	Camera(double fov);
	Camera(Vec3 eye, Vec3 target, double fov = 90.0f);

	void Translate(Vec3 pos) { _eye = pos; }
	void LookAt(Vec3 loc) { _target = loc; } 
	void SetFov(double fov) {  _fov = fov; }

	Vec3 GetEye() const { return _eye; }
	Vec3 GetTarget() const { return _target; }
	Vec3 GetUp() const { return _up; }
	double GetFOV() const { return _fov; }
};