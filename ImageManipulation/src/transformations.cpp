#include "pch.h"
#include <algorithm>

namespace ImageManipulation {
	void Image::flip(FlipDirection direction) {
		auto height = dimensions.first >> (direction == FlipDirection::VERTICAL ? 1 : 0);
		auto width = dimensions.second >> (direction == FlipDirection::HORIZONTAL ? 1 : 0);

		for(auto i = 0u; i < height; i++)
			for(auto j = 0u; j < width; j++) {
				Dimensions first_coordinate { i, j };
				Dimensions second_coordinate {
					direction == FlipDirection::VERTICAL ? dimensions.first - 1 - i : i,
					direction == FlipDirection::HORIZONTAL ? dimensions.second - 1 - j : j
				};

				auto first_pixel = get_pixel(first_coordinate);
				auto second_pixel = get_pixel(second_coordinate);

				std::swap_ranges(first_pixel, first_pixel + pixel_size, second_pixel);
			}
	}

	void Image::rotate(RotationDirection direction) {

	}
}