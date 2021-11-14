#include "pch.hpp"

namespace ImageManipulation {
Image::Image(Dimensions dimensions, uint16_t pixelSize, uint32_t headerSize)
	: dimensions(dimensions), pixelSize(pixelSize), headerSize(headerSize) {
	header = new byte[headerSize];
	data = new byte[getDataSize()];
}

Image::~Image() {
	delete data;
}

const byte* Image::getPixel(Coordinates coordinate) const {
	auto offset = ((ull)coordinate.y * dimensions.width + coordinate.x) * pixelSize;
	return data + offset;
}

byte* Image::getPixel(Coordinates coordinate) {
	auto offset = ((ull)coordinate.y * dimensions.width + coordinate.x) * pixelSize;
	return data + offset;
}

Dimensions Image::getDimensions() const {
	return dimensions;
}

uint16_t Image::getPixelSize() const {
	return pixelSize;
}

ull Image::getDataSize() const {
	return (ull)dimensions.height * dimensions.width * pixelSize;
}
}