
#include "RayTracer.h"
#include "Scene.h"
#include "ImageBuffer.h"

#include <iostream>
#include <string>
#include <memory>

std::shared_ptr<Scene> GenerateScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

	scene->AddPointLight(PointLight{ {  0.0, 3.0, 0.0 }, { 0.5, 1.0, 0.4 }, 10.0 });
	scene->AddPointLight(PointLight{ { -0.75, 0.5, 0.0 }, { 0.3, 0.1, 1.0 }, 5.0 });

	std::initializer_list<Vec3> vertices = 
	{
		// Front Face
		{ -0.5f, -0.5f,  0.5f },
		{  0.5f, -0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f },
		{ -0.5f, -0.5f,  0.5f },

		// Right Face
		{  0.5f, -0.5f,  0.5f },
		{  0.5f, -0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f,  0.5f },
		{  0.5f, -0.5f,  0.5f },

		// Back Face
		{  0.5f, -0.5f, -0.5f },
		{ -0.5f, -0.5f, -0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },

		// Left Face
		{ -0.5f, -0.5f, -0.5f },
		{ -0.5f, -0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{ -0.5f, -0.5f, -0.5f },

		// Top Face
		{ -0.5f,  0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{ -0.5f,  0.5f,  0.5f },

		// Bottom Face
		{ -0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f,  0.5f },
		{  0.5f, -0.5f,  0.5f },
		{ -0.5f, -0.5f,  0.5f },
		{ -0.5f, -0.5f, -0.5f }
	};

	std::initializer_list<Vec3> normals =
	{
		{  0.0f,  0.0f,  1.0f },
		{  0.0f,  0.0f,  1.0f },
		{  1.0f,  0.0f,  0.0f },
		{  1.0f,  0.0f,  0.0f },
		{  0.0f,  0.0f, -1.0f },
		{  0.0f,  0.0f, -1.0f },
		{ -1.0f,  0.0f,  0.0f },
		{ -1.0f,  0.0f,  0.0f },
		{  0.0f,  1.0f,  0.0f },
		{  0.0f,  1.0f,  0.0f },
		{  0.0f, -1.0f,  0.0f },
		{  0.0f, -1.0f,  0.0f }
	};

	std::initializer_list<Color> colors =
	{
		{ 1.0f, 0.2f, 0.1f },
		{ 1.0f, 0.2f, 0.1f },
		{ 0.2f, 1.0f, 0.1f },
		{ 0.2f, 1.0f, 0.1f },
		{ 0.2f, 0.1f, 1.0f },
		{ 0.2f, 0.1f, 1.0f },
		{ 1.0f, 0.1f, 1.0f },
		{ 1.0f, 0.1f, 1.0f },
		{ 1.0f, 1.0f, 0.2f },
		{ 1.0f, 1.0f, 0.2f },
		{ 0.2f, 1.0f, 1.0f },
		{ 0.2f, 1.0f, 1.0f }
	};

	std::initializer_list<Vec3> plane_vertices =
	{
		{ -0.5f,  0.0f,  0.5f },
		{  0.5f,  0.0f,  0.5f },
		{  0.5f,  0.0f, -0.5f },
		{  0.5f,  0.0f, -0.5f },
		{ -0.5f,  0.0f, -0.5f },
		{ -0.5f,  0.0f,  0.5f }
	};

	std::initializer_list<Vec3> plane_normals =
	{
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f }
	};

	Material cube_material;
	cube_material.color = { 1.0f, 1.0f, 1.0f };
	cube_material.reflection = 0.8;
	cube_material.diffuse = 1.0;
	cube_material.shine = 64.0;
	cube_material.transmission = 0.0;

	std::shared_ptr<Mesh> cube1 = std::make_shared<Mesh>(vertices, normals, colors, cube_material);

	cube_material.reflection = 0.0;
	cube_material.transmission = 0.0;

	std::shared_ptr<Mesh> cube2 = std::make_shared<Mesh>(vertices, normals, colors, cube_material);

	cube_material.reflection = 0.0;
	cube_material.transmission = 0.0;

	std::shared_ptr<Mesh> cube3 = std::make_shared<Mesh>(vertices, normals, colors, cube_material);
	
	cube1->Translate({ 0.0, 0.01, 0.0 });

	cube2->RotateX(-35.0);
	cube2->Translate({ 0.5, 1.0, -1.5 });
	
	cube1->RotateY(60.0);
	cube1->Translate({ -1.5, -0.5, -0.5 });
	cube1->Scale({ 1.0, 0.5, 1.0 });

	cube3->RotateY(45.0);
	cube3->RotateX(45.0);
	cube3->Translate({ 2.5, 1.0, -1.0 });

	scene->AddMesh(cube1);
	scene->AddMesh(cube2);
	scene->AddMesh(cube3);

	Material plane_material;
	plane_material.color = { 1.0, 1.0, 1.0 };
	plane_material.reflection = 0.0;
	plane_material.diffuse = 1.0;

	std::shared_ptr<Mesh> plane = std::make_shared<Mesh>(plane_vertices, plane_normals, plane_material);
	
	plane->Scale(Vec3{ 1000.0 });
	plane->Translate({ 0.0, -0.5, 0.0 });

	scene->AddMesh(plane);

	Material sphere_material;
	sphere_material.color = Vec3{ 0.0, 1.0, 0.0 };
	sphere_material.diffuse = 1.0;
	sphere_material.reflection = 0.5;
	sphere_material.transmission = 0.8;
	sphere_material.refractive_index = 1.01;

	scene->AddSphere({ { 0.5, 0.01, 0.5 }, 0.5, sphere_material });

	Camera &cam = scene->GetCamera();
	cam.Translate({ 0.25, 0.0, 2.0 });

	scene->Build();
	return scene;
}

// TODO:
//	- Model and Scene loading
//  - Random multisampling
//	- Instrumentation
//	- Use BVH acceleration
//	- Multithreading
//  - Material CPU shaders and BSDFs
//		- Fresnel and other lighting effects (Beer's law maybe...)
//		- Texture sampling and triangle surface interpolation
//		- Caustics
//	- Light interfaces
//		- Area lights
//		- Spot lights
//  - Global illumination
//  - Nvidia CUDA core compute
//
int main(int argc, char **argv)
{	
	ImageBuffer target(1920, 1920);

	RayTracerConfig config;
	config.scene = std::move(GenerateScene());
	config.samples = 2;
	config.ray_depth = 16;
	config.skybox = Color{ 0.0 };

	RayTracer tracer(std::move(config));

	tracer.Draw(target);

	std::string output_path{ "./out.png" };

	if (argc > 1)
		output_path = argv[1];
		
	if (!target.WriteToFile(output_path))
	{
		std::cerr << "Failed to create output path '" << output_path << "'." << std::endl;
		return -1;
	}

	std::cout << "Output written to: '" << output_path << "'" << std::endl;
	return 0;
}