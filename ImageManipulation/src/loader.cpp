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
	stream.read(reinterpret_cast<byte*>(&headerSize), sizeof(HeaderMetric));

	stream.seekg(0x12);
	stream.read(reinterpret_cast<byte*>(&dimensions.width), sizeof(ImageMetric));
	stream.read(reinterpret_cast<byte*>(&dimensions.height), sizeof(ImageMetric));

	stream.seekg(0x1C);
	PixelMetric totalPixelSize;
	stream.read(reinterpret_cast<byte*>(&totalPixelSize), sizeof(PixelMetric));
	pixelSize = totalPixelSize / CHAR_BIT;

	stream.clear();
	stream.seekg(0);

	header.resize(headerSize);
	stream.read(header.data(), headerSize);

	uint8_t padding = ((DataMetric)dimensions.width * pixelSize) % 4;
	if(padding)
		padding = 4 - padding;

	data.resize(getDataSize());
	for(ImageMetric i = 0; i < dimensions.height; i++) {
		stream.read(getPixel({ i, 0 }).data(), (DataMetric)dimensions.width * pixelSize);

		stream.seekg(padding, std::ios::cur);
	}
}

void Image::saveImage(std::ofstream& stream) const {
	stream.clear();
	stream.seekp(0);

	stream.write(header.data(), headerSize);

	uint8_t padding = ((DataMetric)dimensions.width * pixelSize) % 4;
	if(padding)
		padding = 4 - padding;

	for(ImageMetric i = 0; i < dimensions.height; i++) {
		stream.write(getPixel({ i, 0 }).data(), (DataMetric)dimensions.width * pixelSize);

		static const byte zero = 0;
		stream.write(&zero, padding);
	}

	stream.seekp(0x12);
	stream.write(reinterpret_cast<const byte*>(&dimensions.width), sizeof(ImageMetric));
	stream.write(reinterpret_cast<const byte*>(&dimensions.height), sizeof(ImageMetric));

	PixelMetric totalPixelSize = pixelSize * CHAR_BIT;
	stream.seekp(0x1C);
	stream.write(reinterpret_cast<const byte*>(&totalPixelSize), sizeof(PixelMetric));
}

void Image::saveImage(const std::string& filePath) const {
	std::ofstream stream(filePath, std::ios::binary);

	saveImage(stream);

	stream.close();
}
}