#pragma once

#include <fstream>
#include <string>

namespace ImageManipulation {
using ull = unsigned long long;
using byte = char;

struct Dimensions {
	uint32_t height;
	uint32_t width;
};

struct Coordinates {
	uint32_t y;
	uint32_t x;
};

enum class FlipDirection : uint8_t {
	NONE = 0,
	HORIZONTAL = 1,
	VERTICAL = 2,
	BOTH = 3
};

enum class RotationDirection : uint8_t {
	LEFT,
	RIGHT
};

class Image {
public:
	Image(Dimensions dimensions, uint16_t pixelSize, uint32_t headerSize);
	Image(std::ifstream& stream);
	Image(const std::string& filePath);

	~Image();

	const byte* getPixel(Coordinates coordinate) const;
	byte* getPixel(Coordinates coordinate);

	Dimensions getDimensions() const;
	unsigned short getPixelSize() const;

	void saveImage(std::ofstream& stream) const;
	void saveImage(const std::string& filePath) const;

	void flip(FlipDirection direction);
	void rotate(RotationDirection direction);

	void invert();
private:
	Dimensions dimensions;
	uint16_t pixelSize;

	byte* data;

	uint32_t headerSize;
	byte* header;

	void loadImage(std::ifstream& stream);
	ull getDataSize() const;
};
}