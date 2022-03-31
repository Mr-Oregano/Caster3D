
#include "RayTracer.h"
#include "Scene.h"
#include "ImageBuffer.h"

#include <iostream>
#include <string>
#include <memory>

// TODO:
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
	std::shared_ptr<Scene> scene = std::make_shared<Scene>("./res/sample.obj", "./res");

	if (!scene)
	{
		std::cerr << "Failed to load scene" << std::endl;
		return -1;
	}

	scene->AddPointLight({ {  3.0, 5.0, -1.0 }, { 0.5, 1.0, 0.4 }, 4.0 });
	scene->AddPointLight({ { -1.0, 3.0,  1.0 }, { 0.3, 0.1, 1.0 }, 5.0 });

	Camera &cam = scene->GetCamera();
	cam.Translate(Vec3{ 0.0, 4.0, 6.0 });

	scene->Build();

	RayTracerConfig config;
	config.scene = scene;
	config.samples = 8;
	config.ray_depth = 8;
	config.skybox = Color{ 0.0 };

	RayTracer tracer(std::move(config));

	std::cout << "Drawing scene..." << std::endl;
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