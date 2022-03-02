
#include "Camera.h"

Camera3D::Camera3D(float fov, float aspect)
    : _view(glm::mat4{1.0f}), _proj(glm::perspective(fov, aspect, 0.1f, 100.f))
{}

void Camera3D::MoveTo(glm::vec3 loc)
{
    _view = glm::translate(glm::mat4{1.0f}, loc);
}

void Camera3D::Rotate(glm::quat rot)
{
    // _view = glm::quat(_view)
}

glm::mat4 Camera3D::CalcViewProj()
{
    return _view * _proj;
}
