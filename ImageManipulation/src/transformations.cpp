#include "pch.hpp"
#include <algorithm>

namespace ImageManipulation {
void Image::flip(FlipDirection direction) {
	auto iteration_height = dimensions.first >> (direction == FlipDirection::VERTICAL ? 1 : 0);;
	auto iteration_width = dimensions.second >> (direction == FlipDirection::HORIZONTAL ? 1 : 0);

	if(direction == FlipDirection::HORIZONTAL) {
		for(auto i = 0u; i < iteration_height; i++) {
			for(auto j = 0u; j < iteration_width; j++) {
				auto first_coordinate = Dimensions { i, j };
				auto second_coordinate = Dimensions { i, dimensions.second - 1 - j };

				auto first_row = get_pixel(first_coordinate);
				auto second_row = get_pixel(second_coordinate);

				std::swap_ranges(first_row, first_row + pixel_size, second_row);
			}
		}
	} else if(direction == FlipDirection::VERTICAL) {
		for(auto i = 0u; i < iteration_height; i++) {
			auto first_coordinate = Dimensions { i, 0 };
			auto second_coordinate = Dimensions { dimensions.first - 1 - i, 0 };

			auto first_row = get_pixel(first_coordinate);
			auto second_row = get_pixel(second_coordinate);

			std::swap_ranges(first_row, first_row + (ull)dimensions.second * pixel_size, second_row);
		}
	}
}

void Image::rotate(RotationDirection direction) {

}
}