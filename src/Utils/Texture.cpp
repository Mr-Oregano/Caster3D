
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

Color Texture2D::Sample(Vec2 uv, TextureSampleParams params)
{
	std::uint32_t max_x = _width - 1;
	std::uint32_t max_y = _height - 1;

	switch (params.wrap)
	{
		case TextureWrap::REPEAT:
			uv = glm::repeat(uv);
			break;
		
		case TextureWrap::MIRROR:
			uv = glm::mirrorRepeat(uv);
			break;

		default: // CLAMP
			uv = glm::clamp(uv);
	}

	std::uint32_t tx = static_cast<std::uint32_t>(uv.x * max_x);
	std::uint32_t ty = static_cast<std::uint32_t>(uv.y * max_y);
	std::uint32_t loc = (tx + ty * _width) * _channels;

	assert(loc < _width *_height *_channels);
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
