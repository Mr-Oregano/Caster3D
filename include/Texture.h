#pragma once

#include "Maths.h"

#include "stb_image/stb_image.h"

#include <string>

enum class TextureFilter
{
	NEAREST,
	LINEAR
};

enum class TextureWrap
{
	REPEAT,
	CLAMP,
	MIRROR
};

struct TextureSampleParams
{
	TextureFilter filter = TextureFilter::LINEAR;
	TextureWrap wrap = TextureWrap::CLAMP;
};

class Texture2D
{
private:
	stbi_uc *_buffer = nullptr;
	std::uint32_t _width = 0;
	std::uint32_t _height = 0;
	int _channels = 0;

public:
	Texture2D(std::string filename);
	~Texture2D();

	Color Sample(Vec2 uv, TextureSampleParams params = {});
};