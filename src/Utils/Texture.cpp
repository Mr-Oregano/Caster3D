
#include "Texture.h"

#include "stb_image/stb_image.h"

Texture2D::Texture2D(std::string filename)
{
	stbi_set_flip_vertically_on_load(true);

	_buffer = stbi_load(filename.c_str(), (int*) &_width, (int*) &_height, &_channels, 0);

	assert(_buffer != nullptr);
}

Texture2D::~Texture2D()
{
	if (_buffer != nullptr)
		stbi_image_free(_buffer);
}

Color Texture2D::Sample(double u, double v, TextureSampleParams params)
{
	std::uint32_t max_x = _width - 1;
	std::uint32_t max_y = _height - 1;

	std::uint32_t tx = static_cast<std::uint32_t>(u * max_x);
	std::uint32_t ty = static_cast<std::uint32_t>(v * max_y);

	switch (params.wrap)
	{
		case TextureWrap::REPEAT:
		{
			tx %= (_width - 1);
			ty %= max_y;
			break;
		}
		case TextureWrap::MIRROR:
		{
			int dir_x = (long long)u % 2;
			int dir_y = (long long)v % 2;

			tx %= max_x;
			ty %= max_y;
			tx = dir_x * max_x + (1 - 2 * dir_x) * tx;
			ty = dir_y * max_y + (1 - 2 * dir_y) * ty;

			break;
		}
		default: // CLAMP
		{
			tx = glm::clamp(tx, (std::uint32_t)0, max_x);
			ty = glm::clamp(ty, (std::uint32_t)0, max_y);
		}
	}

	std::uint32_t loc = (tx + ty * _width) * _channels;
	
	assert(loc < _width * _height * _channels);
	assert(_channels >= 3);

	switch (params.filter)
	{
		// TODO: Implement LINEAR filtering.
		case TextureFilter::LINEAR:
		
		default: // NEAREST
		{
			double r = glm::clamp(_buffer[loc + 0] / 255.0, 0.0, 1.0);
			double g = glm::clamp(_buffer[loc + 1] / 255.0, 0.0, 1.0);
			double b = glm::clamp(_buffer[loc + 2] / 255.0, 0.0, 1.0);

			return { r, g, b };
		}
	}

	
}

Color Texture2D::Sample(Vec2 uv, TextureSampleParams params)
{
	return Sample(uv.x, uv.y, params);
}
