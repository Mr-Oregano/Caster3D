
#include "RayTracer.h"
#include "Scene.h"
#include "ImageBuffer.h"

#include <iostream>
#include <string>
#include <memory>
#include <chrono>

// TODO:
//	- Instrumentation
//	- Multithreading
//  - Material CPU shaders and BSDFs
//		- Fresnel and other lighting effects (Beer's law maybe...)
//		- Texture sampling
//		- Caustics
//	- Light interfaces
//		- Area lights
//		- Spot lights
//  - Global illumination
//  - Nvidia CUDA core compute
//
int main(int argc, char **argv)
{	
	ImageBuffer target(512, 512);
	std::shared_ptr<Scene> scene = std::make_shared<Scene>("./res/sample.obj", "./res");

	if (!scene)
	{
		std::cerr << "Failed to load scene" << std::endl;
		return -1;
	}

	// scene->AddDirLight({ Vec3{ -1.0, -10.0, 1.5 }, Color{ 1.0 }, 0.1 });
	scene->AddPointLight({ {  3.0, 5.0, -1.0 }, { 0.5, 1.0, 0.4 }, 4.0 });
	scene->AddPointLight({ { -1.0, 3.0,  1.0 }, { 0.3, 0.1, 1.0 }, 5.0 });

	Camera &cam = scene->GetCamera();
	cam.Translate(Vec3{ 4.0, 2.0, 4.0 });
	cam.LookAt(Vec3{ 0.0, 0.5, 0.0 });

	scene->Build();

	RayTracerConfig config;
	config.scene = scene;
	config.samples = 10;
	config.ray_depth = 1;
	config.skybox = Color{ 0.0 };

	RayTracer tracer(std::move(config));

	std::cout << "Drawing scene..." << std::endl;
	
	std::chrono::high_resolution_clock clock;
	auto start = clock.now();
	tracer.Draw(target);
	auto end = clock.now();

	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	metrics.avg_hit_tests_per_raycast /= metrics.raycast_count;
	metrics.avg_raycasts_per_pixel /= metrics.pixel_count;

	std::cout << std::endl << "Metrics:" << std::endl;
	std::cout << "Took " << duration / 1000.0 << " seconds..." << std::endl;
	std::cout << "Pixels: " << metrics.pixel_count << std::endl;
	std::cout << "Samples: " << metrics.samples_per_pixel << std::endl;
	std::cout << "Raycasts: " << metrics.raycast_count << std::endl;
	std::cout << "Triangles: " << metrics.triangle_count << std::endl;
	std::cout << "BVH Size: " << metrics.bvh_size << std::endl;
	std::cout << "Avg Hit Tests Per Raycast: " << metrics.avg_hit_tests_per_raycast << std::endl;
	std::cout << "Avg Raycasts Per pixel: " << metrics.avg_raycasts_per_pixel << std::endl;

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