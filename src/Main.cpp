
#include "RayTracer.h"
#include "Scene.h"
#include "ImageBuffer.h"

#include <stb_image/stb_image_write.h>

#include <string>
#include <memory>

void WriteOutput(const std::string &filename, const ImageBuffer &buffer, int compression = 3)
{
	auto [width, height] = buffer.GetExtent();

	std::uint8_t bpp = buffer.GetBytesPerPixel();

	stbi_write_png(filename.c_str(), width, height, compression, buffer.GetBuffer(), width * bpp);
}

std::shared_ptr<Scene> GenerateScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

	scene->AddDirLight(DirectionalLight{ glm::dvec3{  -1.0,  -1.0,  -1.0 }, glm::dvec3{ 1.0 } });
	scene->AddPointLight(PointLight{ glm::dvec3{  12.0, 7.5, -10.0 }, glm::dvec3{ 0.5, 1.0, 0.4 }, 100.0 });
	scene->AddPointLight(PointLight{ glm::dvec3{ -0.75,  0.5, 0.0 }, glm::dvec3{ 0.3, 0.1, 1.0 }, 5.0 });

	Material cube_material;
	cube_material.color = glm::vec3{ 1.0f, 1.0f, 1.0f };
	cube_material.reflection = 0.75;
	cube_material.diffuse = 1.0;
	cube_material.specular = 1.0;
	cube_material.shine = 64.0;

	Triangle cube_triangles[12];

	// Front Face
	cube_triangles[0].v0 = { -0.5f, -0.5f,  0.5f };
	cube_triangles[0].v1 = { 0.5f, -0.5f,  0.5f };
	cube_triangles[0].v2 = { 0.5f,  0.5f,  0.5f };
	cube_triangles[0].normal = { 0.0f, 0.0f, 1.0f };
	cube_triangles[0].color = { 1.0f, 0.2f, 0.1f };

	cube_triangles[1].v0 = { 0.5f,  0.5f,  0.5f };
	cube_triangles[1].v1 = { -0.5f,  0.5f,  0.5f };
	cube_triangles[1].v2 = { -0.5f, -0.5f,  0.5f };
	cube_triangles[1].normal = { 0.0f, 0.0f, 1.0f };
	cube_triangles[1].color = { 1.0f, 0.2f, 0.1f };

	// Left Face		
	cube_triangles[2].v0 = { 0.5f, -0.5f,  0.5f };
	cube_triangles[2].v1 = { 0.5f, -0.5f, -0.5f };
	cube_triangles[2].v2 = { 0.5f,  0.5f, -0.5f };
	cube_triangles[2].normal = { 1.0f, 0.0f, 0.0f };
	cube_triangles[2].color = { 0.2f, 1.0f, 0.1f };

	cube_triangles[3].v0 = { 0.5f,  0.5f, -0.5f };
	cube_triangles[3].v1 = { 0.5f,  0.5f,  0.5f };
	cube_triangles[3].v2 = { 0.5f, -0.5f,  0.5f };
	cube_triangles[3].normal = { 1.0f, 0.0f, 0.0f };
	cube_triangles[3].color = { 0.2f, 1.0f, 0.1f };

	// Back Face
	cube_triangles[4].v0 = { 0.5f, -0.5f, -0.5f };
	cube_triangles[4].v1 = { -0.5f, -0.5f, -0.5f };
	cube_triangles[4].v2 = { -0.5f,  0.5f, -0.5f };
	cube_triangles[4].normal = { 0.0f, 0.0f, -1.0f };
	cube_triangles[4].color = { 0.2f, 0.1f, 1.0f };

	cube_triangles[5].v0 = { -0.5f,  0.5f, -0.5f };
	cube_triangles[5].v1 = { 0.5f,  0.5f, -0.5f };
	cube_triangles[5].v2 = { 0.5f, -0.5f, -0.5f };
	cube_triangles[5].normal = { 0.0f, 0.0f, -1.0f };
	cube_triangles[5].color = { 0.2f, 0.1f, 1.0f };

	// Right Face
	cube_triangles[6].v0 = { -0.5f, -0.5f, -0.5f };
	cube_triangles[6].v1 = { -0.5f, -0.5f,  0.5f };
	cube_triangles[6].v2 = { -0.5f,  0.5f,  0.5f };
	cube_triangles[6].normal = { -1.0f, 0.0f, 0.0f };
	cube_triangles[6].color = { 1.0f, 0.1f, 1.0f };

	cube_triangles[7].v0 = { -0.5f,  0.5f,  0.5f };
	cube_triangles[7].v1 = { -0.5f,  0.5f, -0.5f };
	cube_triangles[7].v2 = { -0.5f, -0.5f, -0.5f };
	cube_triangles[7].normal = { -1.0f, 0.0f, 0.0f };
	cube_triangles[7].color = { 1.0f, 0.1f, 1.0f };

	// Top Face
	cube_triangles[8].v0 = { -0.5f,  0.5f,  0.5f };
	cube_triangles[8].v1 = { 0.5f,  0.5f,  0.5f };
	cube_triangles[8].v2 = { 0.5f,  0.5f, -0.5f };
	cube_triangles[8].normal = { 0.0f, 1.0f, 0.0f };
	cube_triangles[8].color = { 1.0f, 1.0f, 0.2f };

	cube_triangles[9].v0 = { 0.5f,  0.5f, -0.5f };
	cube_triangles[9].v1 = { -0.5f,  0.5f, -0.5f };
	cube_triangles[9].v2 = { -0.5f,  0.5f,  0.5f };
	cube_triangles[9].normal = { 0.0f, 1.0f, 0.0f };
	cube_triangles[9].color = { 1.0f, 1.0f, 0.2f };

	// Bottom Face
	cube_triangles[10].v0 = { -0.5f, -0.5f, -0.5f };
	cube_triangles[10].v1 = { 0.5f, -0.5f, -0.5f };
	cube_triangles[10].v2 = { 0.5f, -0.5f,  0.5f };
	cube_triangles[10].normal = { 0.0f, -1.0f, 0.0f };
	cube_triangles[10].color = { 0.2f, 1.0f, 1.0f };

	cube_triangles[11].v0 = { 0.5f, -0.5f,  0.5f };
	cube_triangles[11].v1 = { -0.5f, -0.5f,  0.5f };
	cube_triangles[11].v2 = { -0.5f, -0.5f, -0.5f };
	cube_triangles[11].normal = { 0.0f, -1.0f, 0.0f };
	cube_triangles[11].color = { 0.2f, 1.0f, 1.0f };

	std::shared_ptr<Mesh> cube1 = std::make_shared<Mesh>(cube_triangles, std::size(cube_triangles), cube_material);

	cube_material.reflection = 0.0;
	std::shared_ptr<Mesh> cube2 = std::make_shared<Mesh>(cube_triangles, std::size(cube_triangles), cube_material);
	std::shared_ptr<Mesh> cube3 = std::make_shared<Mesh>(cube_triangles, std::size(cube_triangles), cube_material);
	std::shared_ptr<Mesh> cube4 = std::make_shared<Mesh>(cube_triangles, std::size(cube_triangles), cube_material);
	
	cube2->RotateX(-35.0);
	cube2->Translate({ 0.5, 1.0, -1.5 });
	
	cube3->RotateY(45.0);
	cube3->Translate({ -1.5, -0.5, -0.5 });
	cube3->Scale({ 1.0, 0.5, 1.0 });

	cube4->RotateY(45.0);
	cube4->RotateX(45.0);
	cube4->Translate({ 2.5, 1.0, -1.0 });

	scene->AddMesh(cube1);
	scene->AddMesh(cube2);
	scene->AddMesh(cube3);
	scene->AddMesh(cube4);

	Material plane_material;
	plane_material.color = { 1.0, 1.0, 1.0 };
	plane_material.reflection = 0.0;
	plane_material.diffuse = 1.0;
	plane_material.specular = 0.0;

	Triangle plane_triangles[2];

	plane_triangles[0].v0 = { -0.5f, 0.0f,  0.5f };
	plane_triangles[0].v1 = { 0.5f, 0.0f,  0.5f };
	plane_triangles[0].v2 = { 0.5f, 0.0f, -0.5f };
	plane_triangles[0].normal = { 0.0f, 1.0f, 0.0f };

	plane_triangles[1].v0 = { 0.5f, 0.0f, -0.5f };
	plane_triangles[1].v1 = { -0.5f, 0.0f, -0.5f };
	plane_triangles[1].v2 = { -0.5f, 0.0f,  0.5f };
	plane_triangles[1].normal = { 0.0f, 1.0f, 0.0f };

	std::shared_ptr<Mesh> plane = std::make_shared<Mesh>(plane_triangles, std::size(plane_triangles), plane_material);
	
	plane->Scale(glm::dvec3{ 1000.0 });
	plane->Translate({ 0.0, -0.5, 0.0 });

	scene->AddMesh(plane);

	Camera &cam = scene->GetCamera();
	cam.Translate(glm::dvec3{ -2.0, 2.0, 2.0 });

	return scene;
}

int main()
{	
	RayTracer tracer(GenerateScene());

	ImageBuffer target(1920, 1920);

	tracer.Draw(target, 2);

	WriteOutput("./output/out.png", target);
}