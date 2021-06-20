#include "pch.h"
#include <fstream>

namespace ImageManipulation {
	Image::Image(std::ifstream& stream) {
		load_image(stream);
	}

	Image::Image(const char* file_path) {
		std::ifstream stream;
		stream.open(file_path, std::ios::binary);

		load_image(stream);

		stream.close();
	}

	void Image::load_image(std::ifstream& stream) {
		stream.seekg(0x0A);
		stream.read(reinterpret_cast<char*>(&header_size), 4);

		stream.seekg(0x12);
		stream.read(reinterpret_cast<char*>(&dimensions.second), 4);
		stream.read(reinterpret_cast<char*>(&dimensions.first), 4);

		stream.seekg(0x1C);
		stream.read(reinterpret_cast<char*>(&pixel_size), 2);
		pixel_size /= CHAR_BIT;

		stream.clear();
		stream.seekg(0);

		header.resize(header_size);
		stream.read(header.data(), header_size);

		auto padding = ((ull)dimensions.second * pixel_size) % 4;
		if(padding)
			padding = 4 - padding;

		data.resize((ull)dimensions.first * dimensions.second * pixel_size);
		for(auto i = 0u; i < dimensions.first; i++) {
			stream.read(&*get_pixel({ i, 0 }), (ull)dimensions.second * pixel_size);

			stream.seekg(padding, std::ios::cur);
		}
	}

	void Image::save_image(std::ofstream& stream) {
		stream.clear();
		stream.seekp(0);

		stream.write(header.data(), header_size);

		auto padding = ((ull)dimensions.second * pixel_size) % 4;
		if(padding)
			padding = 4 - padding;

		auto zero = '\0';
		for(auto i = 0u; i < dimensions.first; i++) {
			stream.write(&*get_pixel({ i, 0 }), (ull)dimensions.second * pixel_size);

			stream.write(&zero, padding);
		}

		stream.seekp(0x12);
		stream.write(reinterpret_cast<char*>(&dimensions.second), 4);
		stream.write(reinterpret_cast<char*>(&dimensions.first), 4);

		auto pixel_size = this->pixel_size * CHAR_BIT;
		stream.seekp(0x1C);
		stream.write(reinterpret_cast<char*>(&pixel_size), 2);
	}

	void Image::save_image(const char* file_path) {
		std::ofstream stream;
		stream.open(file_path, std::ios::binary);

		save_image(stream);

		stream.close();
	}
}