#include "pch.hpp"

namespace ImageManipulation {
Image::Image(Dimensions dimensions, PixelMetric pixelSize, HeaderMetric headerSize)
	: dimensions(dimensions), pixelSize(pixelSize), headerSize(headerSize) {
	header = new byte[headerSize];
	data = new byte[getDataSize()];
}

Image::~Image() {
	delete data;
}

const byte* Image::getPixel(Coordinates coordinate) const {
	auto offset = ((DataMetric)coordinate.y * dimensions.width + coordinate.x) * pixelSize;
	return data + offset;
}

byte* Image::getPixel(Coordinates coordinate) {
	auto offset = ((DataMetric)coordinate.y * dimensions.width + coordinate.x) * pixelSize;
	return data + offset;
}

Dimensions Image::getDimensions() const {
	return dimensions;
}

PixelMetric Image::getPixelSize() const {
	return pixelSize;
}

DataMetric Image::getDataSize() const {
	return (DataMetric)dimensions.height * dimensions.width * pixelSize;
}
}