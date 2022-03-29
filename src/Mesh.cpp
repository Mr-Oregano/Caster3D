
#include "Mesh.h"

#include <cstring>
#include <algorithm>

Mesh::Mesh(const VertexList &vertices, const NormalsList &normals, const Material &material)
	: Mesh(vertices, normals, {}, material)
{}

Mesh::Mesh(const VertexList &vertices, const NormalsList &normals, const ColorsList &colors, const Material &material)
	: _material(material)
{
	// NOTE: Temporary, currently assuming triangulated vertices. One normal
	//		 per every 3 vertices.
	//
	assert(normals.size() * 3 == vertices.size());
	assert(colors.size() == 0 || colors.size() == normals.size());

	_triangles.reserve(normals.size());

	for (int i = 0; i < normals.size(); ++i)
	{
		if (colors.size() > 0)
			_triangles.emplace_back(Triangle{ 
				*(vertices.begin() + (3 * i + 0)),
				*(vertices.begin() + (3 * i + 1)),
				*(vertices.begin() + (3 * i + 2)),
				*(normals.begin() + i),
				*(colors.begin() + i),
				&_material
			});
		else
			_triangles.emplace_back(Triangle{
				*(vertices.begin() + (3 * i + 0)),
				*(vertices.begin() + (3 * i + 1)),
				*(vertices.begin() + (3 * i + 2)),
				*(normals.begin() + i),
				&_material
			});
	}
}

void Mesh::Transform(const Mat4 &model)
{
	Mat3 normMat = Mat3(glm::transpose(glm::inverse(model)));
	std::for_each(_triangles.begin(), _triangles.end(), [&](Triangle &t){ t.Transform(model, normMat); });
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


