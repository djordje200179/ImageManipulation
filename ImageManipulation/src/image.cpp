#include "pch.hpp"

namespace ImageManipulation {
Image::Image(Dimensions dimensions, PixelMetric pixelSize, HeaderMetric headerSize)
	: dimensions(dimensions), pixelSize(pixelSize), headerSize(headerSize) {
	header.resize(headerSize);
	data.resize(getDataSize());
}

ConstPixel Image::getPixel(Coordinates coordinate) const {
	auto pointer = getPixelPointer(coordinate);
	auto view = std::span(pointer, pixelSize);

	return view;
}

Pixel Image::getPixel(Coordinates coordinate) {
	auto pointer = getPixelPointer(coordinate);
	auto view = std::span(pointer, pixelSize);

	return view;
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

const byte* Image::getPixelPointer(Coordinates coordinate) const {
	auto offset = ((DataMetric)coordinate.y * dimensions.width + coordinate.x) * pixelSize;
	return data.data() + offset;
}

byte* Image::getPixelPointer(Coordinates coordinate) {
	auto offset = ((DataMetric)coordinate.y * dimensions.width + coordinate.x) * pixelSize;
	return data.data() + offset;
}
}