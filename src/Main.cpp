
#include "RayTracer.h"

#include <stb_image/stb_image_write.h>
#include <cstdint>

static const int output_width = 1920;
static const int output_height = 1080;

int main()
{
	std::uint8_t *image_buffer = new std::uint8_t[output_width * output_height * 3];

	RayTracer tracer(nullptr, nullptr, nullptr);

	tracer.Draw(output_width, output_height, image_buffer);

	stbi_write_png("./output/out.png", output_width, output_height, 3, image_buffer, output_width * 3);

	delete [] image_buffer;
}