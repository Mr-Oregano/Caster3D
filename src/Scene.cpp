
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
		material.specular = { m.specular[0], m.specular[1], m.specular[2] };
		material.diffuse = { m.diffuse[0], m.diffuse[1], m.diffuse[2] };
		material.ambient = { m.ambient[0], m.ambient[1], m.ambient[2] };
		material.refractive_index = m.ior;
		material.shine = m.shininess;
		material.reflection = m.metallic;
		material.transmissivity = 1.0 - m.dissolve;
		
		_materials.push_back(material);

		std::cout << m.name << ":" << std::endl;
		std::cout << "\t- Specular: (" << material.diffuse.r << ", " << material.diffuse.g << ", " << material.diffuse.b << ")" << std::endl;
		std::cout << "\t- Diffuse: (" << material.diffuse.r << ", " << material.diffuse.g << ", " << material.diffuse.b << ")" << std::endl;
		std::cout << "\t- Ambient: (" << material.diffuse.r << ", " << material.diffuse.g << ", " << material.diffuse.b << ")" << std::endl;
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
	std::cout << "Scene triangle count: " << _triangles.size() << std::endl;

	std::sort(_triangles.begin(), _triangles.end(), [](const Triangle &t1, const Triangle &t2)
	{
		return t1.GetAABB().bl.x > t2.GetAABB().bl.x;
	});

	std::size_t bvh_max_size = _triangles.size();

	// Determine the next power of 2, minus one
	bvh_max_size |= bvh_max_size >> 1;
	bvh_max_size |= bvh_max_size >> 2;
	bvh_max_size |= bvh_max_size >> 4;
	bvh_max_size |= bvh_max_size >> 8;
	bvh_max_size |= bvh_max_size >> 16;
	bvh_max_size |= bvh_max_size >> 32;

	_bounds.reserve(bvh_max_size);
	_root = SplitBVH(0, _triangles.size() - 1);

	std::cout << "Bounding box count: " << _bounds.size() << std::endl;
	_built = true;
}

HitResult Scene::RayCast(const Ray &ray)
{
	// NOTE: The scene must have been built before we can raycast
	assert(_built);

	return _root->Hit(ray);
}

Volume *Scene::SplitBVH(std::size_t left, std::size_t right)
{
	// NOTE: We DO NOT want to expand past the current capacity for the risk
	//		 of invalidating all the pointers we have gathered.
	//
	assert(_bounds.size() <= _bounds.capacity());

	if (right - left < 2)
	{
		_bounds.emplace_back(BoundingVolume{ &_triangles[left], &_triangles[right] });
		return &_bounds[_bounds.size() - 1];
	}

	std::size_t center = (left + right) / 2;
	Volume *left_bvh = SplitBVH(left, center);
	Volume *right_bvh = SplitBVH(center + 1, right);
	_bounds.emplace_back(BoundingVolume{ left_bvh, right_bvh });

	return &_bounds[_bounds.size() - 1];
}
