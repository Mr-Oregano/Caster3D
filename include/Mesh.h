#pragma once

#include "Triangle.h"
#include "Maths.h"

#include <vector>

class Mesh
{
private:
	std::vector<Triangle> _triangles;
	Material _material;

public:
	Mesh(const Triangle triangles[], std::size_t count, const Material &material);
	virtual ~Mesh() = default;

	void Transform(const Mat4 &model);
	void Translate(const Vec3 &pos);
	void Scale(const Vec3 &scale);
	void Rotate(double degrees, const Vec3 &axis);
	void RotateX(double degrees);
	void RotateY(double degrees);
	void RotateZ(double degrees);
		
	const std::vector<Triangle>& GetTriangleList() const { return _triangles; }
	const Material& GetMaterial() const { return _material; }
};

