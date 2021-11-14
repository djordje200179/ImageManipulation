#include "pch.hpp"
#include <fstream>

namespace ImageManipulation {
Image::Image(std::ifstream& stream) {
	loadImage(stream);
}

Image::Image(const std::string& filePath) {
	std::ifstream stream(filePath, std::ios::binary);

	loadImage(stream);

	stream.close();
}

void Image::loadImage(std::ifstream& stream) {
	stream.seekg(0x0A);
	stream.read(reinterpret_cast<byte*>(&headerSize), 4);

	stream.seekg(0x12);
	stream.read(reinterpret_cast<byte*>(&dimensions.width), 4);
	stream.read(reinterpret_cast<byte*>(&dimensions.height), 4);

	stream.seekg(0x1C);
	stream.read(reinterpret_cast<byte*>(&pixelSize), 2);
	pixelSize /= CHAR_BIT;

	stream.clear();
	stream.seekg(0);

	header = new byte[headerSize];
	stream.read(header, headerSize);

	uint8_t padding = ((DataMetric)dimensions.width * pixelSize) % 4;
	if(padding)
		padding = 4 - padding;

	data = new byte[getDataSize()];
	for(ImageMetric i = 0; i < dimensions.height; i++) {
		stream.read(getPixel({ i, 0 }), (DataMetric)dimensions.width * pixelSize);

		stream.seekg(padding, std::ios::cur);
	}
}

void Image::saveImage(std::ofstream& stream) const {
	stream.clear();
	stream.seekp(0);

	stream.write(header, headerSize);

	uint8_t padding = ((DataMetric)dimensions.width * pixelSize) % 4;
	if(padding)
		padding = 4 - padding;

	for(ImageMetric i = 0; i < dimensions.height; i++) {
		stream.write(getPixel({ i, 0 }), (DataMetric)dimensions.width * pixelSize);

		static const byte zero = 0;
		stream.write(&zero, padding);
	}

	stream.seekp(0x12);
	stream.write(reinterpret_cast<const char*>(&dimensions.width), 4);
	stream.write(reinterpret_cast<const char*>(&dimensions.height), 4);

	PixelMetric pixelSize = this->pixelSize * CHAR_BIT;
	stream.seekp(0x1C);
	stream.write(reinterpret_cast<const char*>(&pixelSize), 2);
}

void Image::saveImage(const std::string& filePath) const {
	std::ofstream stream(filePath, std::ios::binary);

	saveImage(stream);

	stream.close();
}
}