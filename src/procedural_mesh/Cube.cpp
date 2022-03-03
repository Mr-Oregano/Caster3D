
#include "Cube.h"

Cube::Cube()
	: Mesh(new Triangle[12], 12)
{
	Material m;
	m.amb_strength = 0.2f;
	m.shininess = 32.0f;
	m.spec_strength = 1.0f;

	// Front Face
	m.color = { 1.0, 0.2, 0.1 };
	_triangles[0].v[0] = { -0.5f, -0.5f,  0.5f };
	_triangles[0].v[1] = { 0.5f, -0.5f,  0.5f };
	_triangles[0].v[2] = { 0.5f,  0.5f,  0.5f };
	_triangles[0].material = m;
	_triangles[0].normal = { 0.0f, 0.0f, 1.0f };

	_triangles[1].v[0] = { 0.5f,  0.5f,  0.5f };
	_triangles[1].v[1] = { -0.5f,  0.5f,  0.5f };
	_triangles[1].v[2] = { -0.5f, -0.5f,  0.5f };
	_triangles[1].material = m;
	_triangles[1].normal = { 0.0f, 0.0f, 1.0f };

	// Left Face		
	m.color = { 0.2, 1.0, 0.2 };
	_triangles[2].v[0] = { 0.5f, -0.5f,  0.5f };
	_triangles[2].v[1] = { 0.5f, -0.5f, -0.5f };
	_triangles[2].v[2] = { 0.5f,  0.5f, -0.5f };
	_triangles[2].material = m;
	_triangles[2].normal = { 1.0f, 0.0f, 0.0f };

	_triangles[3].v[0] = { 0.5f,  0.5f, -0.5f };
	_triangles[3].v[1] = { 0.5f,  0.5f,  0.5f };
	_triangles[3].v[2] = { 0.5f, -0.5f,  0.5f };
	_triangles[3].material = m;
	_triangles[3].normal = { 1.0f, 0.0f, 0.0f };

	// Back Face
	m.color = { 0.2, 0.1, 1.0 };
	_triangles[4].v[0] = { 0.5f, -0.5f, -0.5f };
	_triangles[4].v[1] = { -0.5f, -0.5f, -0.5f };
	_triangles[4].v[2] = { -0.5f,  0.5f, -0.5f };
	_triangles[4].material = m;
	_triangles[4].normal = { 0.0f, 0.0f, -1.0f };

	_triangles[5].v[0] = { -0.5f,  0.5f, -0.5f };
	_triangles[5].v[1] = { 0.5f,  0.5f, -0.5f };
	_triangles[5].v[2] = { 0.5f, -0.5f, -0.5f };
	_triangles[5].material = m;
	_triangles[5].normal = { 0.0f, 0.0f, -1.0f };

	// Right Face
	m.color = { 1.0, 0.2, 1.0 };
	_triangles[6].v[0] = { -0.5f, -0.5f, -0.5f };
	_triangles[6].v[1] = { -0.5f, -0.5f,  0.5f };
	_triangles[6].v[2] = { -0.5f,  0.5f,  0.5f };
	_triangles[6].material = m;
	_triangles[6].normal = { -1.0f, 0.0f, 0.0f };

	_triangles[7].v[0] = { -0.5f,  0.5f,  0.5f };
	_triangles[7].v[1] = { -0.5f,  0.5f, -0.5f };
	_triangles[7].v[2] = { -0.5f, -0.5f, -0.5f };
	_triangles[7].material = m;
	_triangles[7].normal = { -1.0f, 0.0f, 0.0f };

	// Top Face
	m.color = { 0.5, 1.0, 1.0 };
	_triangles[8].v[0] = { -0.5f,  0.5f,  0.5f };
	_triangles[8].v[1] = { 0.5f,  0.5f,  0.5f };
	_triangles[8].v[2] = { 0.5f,  0.5f, -0.5f };
	_triangles[8].material = m;
	_triangles[8].normal = { 0.0f, 1.0f, 0.0f };

	_triangles[9].v[0] = { 0.5f,  0.5f, -0.5f };
	_triangles[9].v[1] = { -0.5f,  0.5f, -0.5f };
	_triangles[9].v[2] = { -0.5f,  0.5f,  0.5f };
	_triangles[9].material = m;
	_triangles[9].normal = { 0.0f, 1.0f, 0.0f };

	// Bottom Face
	m.color = { 1.0, 1.0, 0.2 };
	_triangles[10].v[0] = { -0.5f, -0.5f, -0.5f };
	_triangles[10].v[1] = { 0.5f, -0.5f, -0.5f };
	_triangles[10].v[2] = { 0.5f, -0.5f,  0.5f };
	_triangles[10].material = m;
	_triangles[10].normal = { 0.0f, -1.0f, 0.0f };

	_triangles[11].v[0] = { 0.5f, -0.5f,  0.5f };
	_triangles[11].v[1] = { -0.5f, -0.5f,  0.5f };
	_triangles[11].v[2] = { -0.5f, -0.5f, -0.5f };
	_triangles[11].material = m;
	_triangles[11].normal = { 0.0f, -1.0f, 0.0f };

}

Cube::~Cube()
{
	delete[] _triangles;
}