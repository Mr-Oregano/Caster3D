
#include "Scene.h"

#include "tiny_obj_loader.h"

#include <algorithm>
#include <iostream>

Scene::Scene(const std::string &filename, const std::string &material_path)
{
	tinyobj::ObjReaderConfig reader_config;
	reader_config.mtl_search_path = material_path;
	reader_config.triangulate = true;

	tinyobj::ObjReader reader;

	if (!reader.ParseFromFile(filename, reader_config))
	{
		if (!reader.Error().empty())
			std::cerr << "TinyObjReader ERROR: " << reader.Error();

		return;
	}

	if (!reader.Warning().empty())
		std::cout << "TinyObjReader WARN: " << reader.Warning();

	auto &attrib = reader.GetAttrib();
	auto &shapes = reader.GetShapes();
	auto &materials = reader.GetMaterials();

	_materials.reserve(materials.size());

	if (!materials.empty())
		std::cout << "Loading Materials..." << std::endl;
	else
		std::cout << "No materials found?" << std::endl;

	for (const auto &m : materials)
	{
		Material material;
		material.color = { m.diffuse[0], m.diffuse[1], m.diffuse[2] };
		material.refractive_index = m.ior;
		material.shine = m.shininess;
		material.reflection = m.metallic;
		material.transmissivity = 1.0 - m.dissolve;
		material.diffuse = 1.0;

		_materials.push_back(material);

		std::cout << m.name << ":" << std::endl;
		std::cout << "\t- Diffuse: (" << material.color.r << ", " << material.color.g << ", " << material.color.b << ")" << std::endl;
		std::cout << "\t- IOR: " << material.refractive_index << std::endl;
		std::cout << "\t- Shine: " << material.shine << std::endl;
		std::cout << "\t- Reflection: " << material.reflection << std::endl;
		std::cout << "\t- Transmissivity: " << material.transmissivity << std::endl;
	}

	for (const auto &s : shapes)
	{
		size_t index_offset = 0;
		for (size_t f = 0; f < s.mesh.num_face_vertices.size(); f++)
		{
			// Sanity check...
			assert(s.mesh.num_face_vertices[f] == 3);

			Vec3 vertices[3];
			Vec3 normals[3];

			for (size_t v = 0; v < 3; v++)
			{
				tinyobj::index_t idx = s.mesh.indices[index_offset + v];

				vertices[v].x = (double)attrib.vertices[3 * size_t(idx.vertex_index) + 0];
				vertices[v].y = (double)attrib.vertices[3 * size_t(idx.vertex_index) + 1];
				vertices[v].z = (double)attrib.vertices[3 * size_t(idx.vertex_index) + 2];

				assert(idx.normal_index >= 0);

				normals[v].x = attrib.normals[3 * size_t(idx.normal_index) + 0];
				normals[v].y = attrib.normals[3 * size_t(idx.normal_index) + 1];
				normals[v].z = attrib.normals[3 * size_t(idx.normal_index) + 2];
			}

			index_offset += 3;
			int mat_id = s.mesh.material_ids[f];

			_triangles.emplace_back(Triangle{
				vertices,
				normals,
				&_materials[mat_id]
			});
		}
	}

	_loaded = true;
}

void Scene::AddSphere(const Sphere &sphere)
{
	assert(!_built && _loaded);

	_spheres.push_back(sphere);
	_volumes.push_back(&*(_spheres.end() - 1));
}

void Scene::AddTriangle(const Triangle &triangle)
{
	assert(!_built && _loaded);

	_triangles.push_back(triangle);
	_volumes.push_back(&*(_triangles.end() - 1));
}

void Scene::AddPointLight(const PointLight &light)
{
	assert(!_built && _loaded);

	_point_lights.push_back(light);
}

void Scene::AddDirLight(const DirectionalLight &light)
{
	assert(!_built && _loaded);

	_dir_lights.push_back(light);
}

void Scene::Build()
{
	assert(!_built && _loaded);

	// TODO: Build bounding volume hierarchy to make raycasts more efficient.

	_volumes.reserve(_triangles.size());

	for (int i = 0; i < _triangles.size(); ++i)
		_volumes.push_back(&_triangles[i]);

	_built = true;
}

HitResult Scene::RayCast(const Ray &ray, double max_distance)
{
	// NOTE: The scene must have been built before we can raycast
	assert(_built);

	HitResult result;
	result.distance = max_distance;

	for (const Volume *v : _volumes)
	{
		HitResult v_hit = v->Hit(ray, max_distance);
		
		// NOTE: Traverse all triangle lists in scene and find the raycast hit with 
		//		 smallest distance.
		// 
		if (v_hit && v_hit.distance < result.distance)
			result = std::move(v_hit);
	}

	return result;
}
