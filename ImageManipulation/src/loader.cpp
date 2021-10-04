#include "pch.hpp"
#include <fstream>

namespace ImageManipulation {
Image::Image(std::ifstream& stream) {
	loadImage(stream);
}

Image::Image(const std::string& file_path) {
	auto stream = std::ifstream(file_path, std::ios::binary);

	loadImage(stream);

	stream.close();
}

void Image::loadImage(std::ifstream& stream) {
	stream.seekg(0x0A);
	stream.read(reinterpret_cast<char*>(&headerSize), 4);

	stream.seekg(0x12);
	stream.read(reinterpret_cast<char*>(&dimensions.second), 4);
	stream.read(reinterpret_cast<char*>(&dimensions.first), 4);

	stream.seekg(0x1C);
	stream.read(reinterpret_cast<char*>(&pixelSize), 2);
	pixelSize /= CHAR_BIT;

	stream.clear();
	stream.seekg(0);

	header.resize(headerSize);
	stream.read(header.data(), headerSize);

	auto padding = ((ull)dimensions.second * pixelSize) % 4;
	if(padding)
		padding = 4 - padding;

	data.resize((ull)dimensions.first * dimensions.second * pixelSize);
	for(auto i = 0u; i < dimensions.first; i++) {
		stream.read(&*getPixel({ i, 0 }), (ull)dimensions.second * pixelSize);

		stream.seekg(padding, std::ios::cur);
	}
}

void Image::saveImage(std::ofstream& stream) const {
	stream.clear();
	stream.seekp(0);

	stream.write(header.data(), headerSize);

	auto padding = ((ull)dimensions.second * pixelSize) % 4;
	if(padding)
		padding = 4 - padding;

	auto zero = '\0';
	for(auto i = 0u; i < dimensions.first; i++) {
		stream.write(&*getPixel({ i, 0 }), (ull)dimensions.second * pixelSize);

		stream.write(&zero, padding);
	}

	stream.seekp(0x12);
	stream.write(reinterpret_cast<const char*>(&dimensions.second), 4);
	stream.write(reinterpret_cast<const char*>(&dimensions.first), 4);

	auto pixelSize = this->pixelSize * CHAR_BIT;
	stream.seekp(0x1C);
	stream.write(reinterpret_cast<const char*>(&pixelSize), 2);
}

void Image::saveImage(const std::string& filePath) const {
	auto stream = std::ofstream(filePath, std::ios::binary);

	saveImage(stream);

	stream.close();
}
}