#pragma once

#include <cstdint>
#include <cstddef>

#include <utility>

class ImageBuffer
{
private:
	std::uint8_t *_buffer = nullptr;
	std::uint32_t _width = 0;
	std::uint32_t _height = 0;

public:
	ImageBuffer(std::uint32_t width, std::uint32_t height);
	~ImageBuffer();

	void WritePixel(std::uint32_t x, std::uint32_t y, double r, double g, double b);
	void WritePixel(std::uint32_t px_i, double r, double g, double b);

	std::pair<std::uint32_t, std::uint32_t> GetExtent() const { return { _width, _height }; }
	std::uint32_t GetBufferSize() const { return _width * _height * _bytes_per_pixel; } 
	std::uint8_t GetBytesPerPixel() const { return _bytes_per_pixel; }
	std::uint8_t* GetBuffer() const { return _buffer; } 

private:
	const static std::uint8_t _bytes_per_pixel = 3;
};