
#include "RayTracer.h"
#include "Scene.h"
#include "ImageBuffer.h"
#include "Metrics.h"

#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <ctime>

#define DEFAULT_OUT_PATH "./out/out.png"
#define DEFAULT_OBJ_PATH "./res/sample.obj"
#define DEFAULT_MAT_PATH "./res"

// TODO:
//	- Instrumentation
//  - BSDFs
//		- Fresnel and other lighting effects (Beer's law maybe...)
//		- Caustics
//  - Nvidia CUDA core compute
//
int main(int argc, char **argv)
{	
	std::string output_path{ DEFAULT_OUT_PATH };

#ifdef _DIST
	std::string obj_path;

	if (argc > 1)
	{
		obj_path = argv[1];

		if (argc > 2)
			output_path = argv[2];
	}
	else
	{
		std::cout << "Enter obj file path: ";
		std::cin >> obj_path;
	}

	std::size_t path_end = obj_path.find_last_of('/');
	std::string mat_path = path_end != std::string::npos ? obj_path.substr(0, path_end)  : ".";
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(obj_path, mat_path, Color{0.0});
#else
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(DEFAULT_OBJ_PATH, DEFAULT_MAT_PATH, Color{ 0.0 });
#endif

	if (!scene)
	{
		std::cerr << "Failed to load scene" << std::endl;
		return -1;
	}

	scene->AddPointLight({ {  3.0, 5.0, -1.0 }, { 0.5, 1.0, 0.4 }, 4.0, 0.05 });
	scene->AddPointLight({ { -1.0, 3.0,  1.0 }, { 0.3, 0.1, 1.0 }, 2.0, 0.05 });
	scene->AddPointLight({ { -1.0, 3.0, 2.0 }, Color{ 1.0 }, 1.0, 0.05 });

	Camera &cam = scene->GetCamera();
	cam.Translate(Vec3{ 4.0, 2.0, 4.0 });
	cam.LookAt(Vec3{ 0.0, 0.5, 0.0 });

	scene->Build();

	ImageBuffer target(512, 512);
	RayTracerConfig config;
	config.samples = 4;
	config.ray_depth = 8;
	config.thread_count = 64;

	RayTracer tracer(std::move(config));

	std::cout << "Drawing scene..." << std::endl;
	
	std::chrono::high_resolution_clock clock;
	auto start = clock.now();
	tracer.Draw(*scene, target);
	auto end = clock.now();

	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	std::cout << "Took " << duration / 1000.0 << " seconds..." << std::endl;

	if (!target.WriteToFile(output_path))
	{
		std::cerr << "Failed to create output path '" << output_path << "'." << std::endl;
		return -1;
	}

	std::cout << "Output written to: '" << output_path << "'" << std::endl;
	return 0;
}