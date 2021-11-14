#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace ImageManipulation {
using ImageMetric = uint32_t;
using DataMetric = uint64_t;
using PixelMetric = uint16_t;
using HeaderMetric = uint32_t;

using byte = char;

struct Dimensions {
	ImageMetric height;
	ImageMetric width;
};

struct Coordinates {
	ImageMetric y;
	ImageMetric x;
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
	Image(Dimensions dimensions, PixelMetric pixelSize, HeaderMetric headerSize);
	Image(std::ifstream& stream);
	Image(const std::string& filePath);

	const byte* getPixel(Coordinates coordinate) const;
	byte* getPixel(Coordinates coordinate);

	Dimensions getDimensions() const;
	PixelMetric getPixelSize() const;

	void saveImage(std::ofstream& stream) const;
	void saveImage(const std::string& filePath) const;

	void flip(FlipDirection direction);
	void rotate(RotationDirection direction);

	void invert();
private: 
	Dimensions dimensions;
	PixelMetric pixelSize;

	std::vector<byte> data;

	HeaderMetric headerSize;
	std::vector<byte> header;

	void loadImage(std::ifstream& stream);
	DataMetric getDataSize() const;
};
}