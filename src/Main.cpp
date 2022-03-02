
#include <stb_image/stb_image_write.h>

#include <cstdint>

int main()
{
	std::uint8_t *image_buffer = new std::uint8_t[512 * 512 * 3];

	for (int i = 0; i < 512 * 512 * 3; i += 3)
	{
		int x = (i / 3) % 512;
		int y = (i / 3) / 512;

		double r, g, b;
		r = x / 512.0;
		g = 1.0;
		b = y / 512.0;

		image_buffer[i + 0] = (int) (r * 255);
		image_buffer[i + 1] = (int) (g * 255);
		image_buffer[i + 2] = (int) (b * 255);
	}

	stbi_write_png("./output/out.png", 512, 512, 3, image_buffer, 512 * 3);

	delete [] image_buffer;
}