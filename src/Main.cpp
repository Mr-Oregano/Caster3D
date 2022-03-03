
#include "RayTracer.h"

#include "Light.h"
#include "Camera.h"
#include "Cube.h"

#include "ImageBuffer.h"

#include <stb_image/stb_image_write.h>

int main()
{	
	Cube cubeMesh;

	glm::mat4 model{ 1.0f };
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3{ 1.0f, 0.0f, 0.0f });
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3{ 0.0f, 1.0f, 0.0f });

	cubeMesh.Transform(model);

	Light light(glm::vec3{ 0.0f, 1.0f, 1.0f }, glm::vec3{ 1.0 });
	Camera3D camera(glm::vec3{ 0.0f, 0.0f, 2.0f }, glm::vec3{ 0.0f });

	RayTracer tracer(&light, &camera, &cubeMesh);

	ImageBuffer target(1920, 1080);

	tracer.Draw(target);

	auto [ width, height ] = target.GetExtent();
	std::uint8_t bpp = target.GetBytesPerPixel();

	stbi_write_png("./output/out.png", width, height, 3, target.GetBuffer(), width * bpp);
}