
#include "Mesh.h"

#include <glm/ext.hpp>

#include <cstring>

Mesh::Mesh(const Triangle triangles[], std::size_t count, const Material &material)
	: _material(material)
{
	_triangles.resize(count);
	std::memcpy(_triangles.data(), triangles, count * sizeof(Triangle));
}

void Mesh::Transform(const glm::mat4 &model)
{
	glm::mat3 normMat = glm::mat3(glm::transpose(glm::inverse(model)));

	for (Triangle &t : _triangles)
	{
		for (int i = 0; i < 3; ++i)
		{
			glm::vec4 v{ t.v[i], 1.0f };

			t.v[i] = glm::vec3{ model * v };
		}

		t.normal = glm::normalize(normMat * t.normal);
	}
}

void Mesh::Translate(const glm::dvec3 &pos)
{
	glm::dmat4 model = glm::translate(glm::dmat4{ 1.0 }, pos);
	Transform(model);
}

void Mesh::Scale(const glm::dvec3 &scale)
{
	glm::dmat4 model = glm::scale(glm::dmat4{ 1.0 }, scale);
	Transform(model);
}

void Mesh::Rotate(double degrees, const glm::dvec3 &axis)
{
	glm::dmat4 model = glm::rotate(glm::dmat4{ 1.0 }, glm::radians(degrees), axis);
	Transform(model);
}

void Mesh::RotateX(double degrees)
{
	Rotate(degrees, glm::dvec3{ 1.0, 0.0, 0.0 });
}

void Mesh::RotateY(double degrees)
{
	Rotate(degrees, glm::dvec3{ 0.0, 1.0, 0.0 });
}

void Mesh::RotateZ(double degrees)
{
	Rotate(degrees, glm::dvec3{ 0.0, 0.0, 1.0 });
}


