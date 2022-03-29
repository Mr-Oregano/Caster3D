#pragma once

#include "Triangle.h"
#include "Maths.h"

#include <vector>


class Mesh
{
private:
	using VertexList = std::initializer_list<Vec3>;
	using NormalsList = std::initializer_list<Vec3>;
	using ColorsList = std::initializer_list<Color>;

	std::vector<Triangle> _triangles;
	Material _material;

public:
	Mesh(const VertexList &vertices, const NormalsList &normals, const Material &material);
	Mesh(const VertexList &vertices, const NormalsList &normals, const ColorsList& colors, const Material &material);
	virtual ~Mesh() = default;

	void Transform(const Mat4 &model);
	void Translate(const Vec3 &pos);
	void Scale(const Vec3 &scale);
	void Rotate(double degrees, const Vec3 &axis);
	void RotateX(double degrees);
	void RotateY(double degrees);
	void RotateZ(double degrees);
		
	const std::vector<Triangle>& GetTriangleList() const { return _triangles; }
	std::size_t GetTriangleCount() const { return _triangles.size(); }
	const Material& GetMaterial() const { return _material; }
};

