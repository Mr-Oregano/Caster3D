
#include "Mesh.h"

#include <cstring>

Mesh::Mesh(const Triangle triangles[], std::size_t count, const Material &material)
	: _material(material)
{
	_triangles.resize(count);
	std::memcpy(_triangles.data(), triangles, count * sizeof(Triangle));
}

void Mesh::Transform(const Mat4 &model)
{
	Mat3 normMat = Mat3(glm::transpose(glm::inverse(model)));

	for (Triangle &t : _triangles)
	{
		for (int i = 0; i < 3; ++i)
		{
			Vec4 v{ t.v[i], 1.0f };

			t.v[i] = Vec3{ model * v };
		}

		t.normal = glm::normalize(normMat * t.normal);
	}
}

void Mesh::Translate(const Vec3 &pos)
{
	glm::dmat4 model = glm::translate(glm::dmat4{ 1.0 }, pos);
	Transform(model);
}

void Mesh::Scale(const Vec3 &scale)
{
	glm::dmat4 model = glm::scale(glm::dmat4{ 1.0 }, scale);
	Transform(model);
}

void Mesh::Rotate(double degrees, const Vec3 &axis)
{
	glm::dmat4 model = glm::rotate(glm::dmat4{ 1.0 }, glm::radians(degrees), axis);
	Transform(model);
}

void Mesh::RotateX(double degrees)
{
	Rotate(degrees, Vec3{ 1.0, 0.0, 0.0 });
}

void Mesh::RotateY(double degrees)
{
	Rotate(degrees, Vec3{ 0.0, 1.0, 0.0 });
}

void Mesh::RotateZ(double degrees)
{
	Rotate(degrees, Vec3{ 0.0, 0.0, 1.0 });
}


