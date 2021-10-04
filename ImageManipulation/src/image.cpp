#include "pch.hpp"

namespace ImageManipulation {
Image::Image(Dimensions dimensions, const unsigned short pixelSize, const unsigned int headerSize)
	: dimensions(dimensions), pixelSize(pixelSize), headerSize(headerSize) {
	data.resize((ull)dimensions.first * dimensions.second * pixelSize);
	header.resize(headerSize);
}

std::vector<char>::const_iterator Image::getPixel(Coordinates coordinate) const {
	std::vector<char>::const_iterator begin = data.begin();
	auto offset = ((ull)coordinate.first * dimensions.second + coordinate.second) * pixelSize;

	return begin + offset;
}

std::vector<char>::iterator Image::getPixel(Coordinates coordinate) {
	auto begin = data.begin();
	auto offset = ((ull)coordinate.first * dimensions.second + coordinate.second) * pixelSize;

	return begin + offset;
}

Dimensions Image::getDimensions() const {
	return dimensions;
}

unsigned short Image::getPixelSize() const {
	return pixelSize;
}
}