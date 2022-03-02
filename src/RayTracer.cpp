
#include "RayTracer.h"

#define STRIDE 3

RayTracer::RayTracer(Light light[], Camera3D *camera, Mesh *mesh)
{
	// TODO
}

void RayTracer::Draw(int width, int height, std::uint8_t *destination)
{
	for (int i = 0; i < width * height * STRIDE; i += STRIDE)
	{
		int x = (i / STRIDE) % width;
		int y = (i / STRIDE) / width;

		double r = x / (double) width;
		double g = 1.0;
		double b = y / (double) height;

		destination[i + 0] = (int)(r * 255);
		destination[i + 1] = (int)(g * 255);
		destination[i + 2] = (int)(b * 255);
	}
}