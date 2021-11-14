#include "pch.hpp"

namespace ImageManipulation {
Image::Image(Dimensions dimensions, uint16_t pixelSize, uint32_t headerSize)
	: dimensions(dimensions), pixelSize(pixelSize), headerSize(headerSize) {
	data.resize((ull)dimensions.height * dimensions.width * pixelSize);
	header.resize(headerSize);
}

std::vector<byte>::const_iterator Image::getPixel(Coordinates coordinate) const {
	std::vector<byte>::const_iterator begin = data.begin();
	auto offset = ((ull)coordinate.y * dimensions.width + coordinate.x) * pixelSize;

	return begin + offset;
}

std::vector<byte>::iterator Image::getPixel(Coordinates coordinate) {
	auto begin = data.begin();
	auto offset = ((ull)coordinate.y * dimensions.width + coordinate.x) * pixelSize;

	return begin + offset;
}

Dimensions Image::getDimensions() const {
	return dimensions;
}

unsigned short Image::getPixelSize() const {
	return pixelSize;
}
}