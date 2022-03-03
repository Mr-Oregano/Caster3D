
#include "Mesh.h"

Mesh::Mesh(Triangle primitives[], std::size_t count)
	: _triangles(primitives), _count(count)
{}

void Mesh::Transform(const glm::mat4 &model)
{
	glm::mat3 normMat = glm::mat3(glm::transpose(glm::inverse(model)));

	for (int i = 0; i < _count; ++i)
	{
		Triangle &t = _triangles[i];

		for (int j = 0; j < 3; ++j)
		{
			glm::vec4 v4{ t.v[j], 1.0f };
			t.v[j] = glm::vec3{ model * v4 };
		}

		t.normal = normMat * t.normal;
	}
}
