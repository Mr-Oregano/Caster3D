
#include "ImageBuffer.h"

#include "Maths.h"

#include <stb_image/stb_image_write.h>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

ImageBuffer::ImageBuffer(std::uint32_t width, std::uint32_t height)
	: _width(width), _height(height)
{
	std::size_t w = _width;
	std::size_t h = _height;
	_buffer = new std::uint8_t[w * h * _bytes_per_pixel];
}

ImageBuffer::~ImageBuffer()
{
	delete[] _buffer;
}

void ImageBuffer::WritePixel(std::uint32_t x, std::uint32_t y, double r, double g, double b)
{
	WritePixel(x + y * _width, r, g, b);
}

void ImageBuffer::WritePixel(std::uint32_t px_i, double r, double g, double b)
{
	r = glm::clamp(r, 0.0, 1.0);
	g = glm::clamp(g, 0.0, 1.0);
	b = glm::clamp(b, 0.0, 1.0);

	px_i *= 3;
	_buffer[px_i + 0] = (int)(r * 255);
	_buffer[px_i + 1] = (int)(g * 255);
	_buffer[px_i + 2] = (int)(b * 255);
}

bool ImageBuffer::WriteToFile(const std::string &filename, int compression)
{
	std::size_t path_end = filename.find_last_of('/');

	if (path_end != std::string::npos)
	{
		std::string dir = filename.substr(0, path_end);

		// NOTE: Create directory if it does not exist.
		if (!fs::is_directory(dir) || !fs::exists(dir))
		{
			fs::create_directory(dir);
			std::cout << "Created directory '" << dir << "'" << std::endl;
		}
	}

	return stbi_write_png(filename.c_str(), _width, _height, compression, _buffer, _width * _bytes_per_pixel) != 0;
}
