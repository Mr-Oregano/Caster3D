
#include "RayTracer.h"

#include "Ray.h"
#include "Triangle.h"
#include "Material.h"

RayTracer::RayTracer(Light *light, Camera3D *camera, Mesh *mesh)
	: _light(light), _camera(camera), _mesh(mesh)
{}

glm::vec3 PhongShading(Light *light, glm::vec3 loc, glm::vec3 n, glm::vec3 view_dir, Material mat)
{
	glm::vec3 light_dir = glm::normalize(light->pos - loc);
	glm::vec3 reflected_light = glm::reflect(-light_dir, n);

	float diff = glm::max(glm::dot(n, light_dir), 0.0f);
	float spec = glm::max(glm::dot(view_dir, reflected_light), 0.0f);

	return (mat.spec_strength * glm::pow(spec, mat.shininess) + diff + mat.amb_strength) * light->color * mat.color;
}

glm::vec3 RayTracer::CastRay(const Ray &ray, Triangle triangles[], std::size_t triangles_count)
{
	HitResult lastResult;
	lastResult.hit = false;
	lastResult.distance = 100.0f;
	
	// NOTE: Traverse all triangle lists in scene and find the raycast hit with 
	//		 smallest distance.
	//
	for (int j = 0; j < triangles_count; ++j)
	{
		HitResult result;
		result.distance = 100.0f;

		if (triangles[j].Hit(ray, result) && result.distance < lastResult.distance)
			lastResult = result;
	}

	if (lastResult.hit)
	{
		glm::vec3 normal = lastResult.normal;
		glm::vec3 light_dir = glm::normalize(_light->pos - lastResult.hit_point);
		glm::vec3 reflected_light = glm::reflect(light_dir, normal);

		return PhongShading(_light, lastResult.hit_point, normal, -ray.dir, std::move(lastResult.material));
	}

	return glm::vec3{0.0f};
}

void RayTracer::Draw(ImageBuffer &target)
{
	auto [ width, height ] = target.GetExtent();
	std::uint8_t stride = target.GetBytesPerPixel();

	double aspect = (double) width / height;

	for (std::uint32_t i = 0; i < target.GetBufferSize(); i += stride)
	{
		int x = (i / stride) % width;
		int y = (i / stride) / width;

		// NOTE: Normalize x and y [-1, 1]. 'y' coordinate needs to be
		//		 flipped so that [bottom, top] maps to [-1, 1]. aspect
		//		 ration needs to be taken into account.
		//
		double nx = aspect * (2.0 * x / width - 1.0);
		double ny = 2.0 * (1.0 - (double) y / height) - 1.0;

		Ray ray(_camera->GetEye(), glm::vec3{nx, ny, _camera->GetEye().z - 1.0f});

		glm::vec3 color = CastRay(ray, _mesh->_triangles, _mesh->_count);

		target.WritePixel(i, color.r, color.g, color.b);
	}
}
