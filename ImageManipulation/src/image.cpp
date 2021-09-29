#include "pch.hpp"

namespace ImageManipulation {
	Image::Image(Dimensions dimensions, const unsigned short pixel_size, const unsigned int header_size)
		: dimensions(dimensions), pixel_size(pixel_size), header_size(header_size) {
		data.resize((ull)dimensions.first * dimensions.second * pixel_size);
		header.resize(header_size);
	}

	std::vector<char>::const_iterator Image::get_pixel(Coordinates coordinate) const {
		std::vector<char>::const_iterator begin = data.begin();
		auto offset = ((ull)coordinate.first * dimensions.second + coordinate.second) * pixel_size;

		return begin + offset;
	}

	std::vector<char>::iterator Image::get_pixel(Coordinates coordinate) {
		auto begin = data.begin();
		auto offset = ((ull)coordinate.first * dimensions.second + coordinate.second) * pixel_size;

		return begin + offset;
	}

	Dimensions Image::get_dimensions() const {
		return dimensions;
	}

	unsigned short Image::get_pixel_size() const {
		return pixel_size;
	}
}