#include "pch.hpp"
#include <algorithm>

namespace ImageManipulation {
void Image::flip(FlipDirection direction) {
	auto iterationHeight = dimensions.first >> (direction == FlipDirection::VERTICAL ? 1 : 0);;
	auto iterationWidth = dimensions.second >> (direction == FlipDirection::HORIZONTAL ? 1 : 0);

	if(direction == FlipDirection::HORIZONTAL) {
		for(auto i = 0u; i < iterationHeight; i++) {
			for(auto j = 0u; j < iterationWidth; j++) {
				Dimensions firstCoordinate { i, j };
				Dimensions secondCoordinate { i, dimensions.second - 1 - j };

				auto firstRow = getPixel(firstCoordinate);
				auto secondRow = getPixel(secondCoordinate);

				std::swap_ranges(firstRow, firstRow + pixelSize, secondRow);
			}
		}
	} else if(direction == FlipDirection::VERTICAL) {
		for(auto i = 0u; i < iterationHeight; i++) {
			Dimensions firstCoordinate { i, 0 };
			Dimensions secondCoordinate { dimensions.first - 1 - i, 0 };

			auto firstRow = getPixel(firstCoordinate);
			auto secondRow = getPixel(secondCoordinate);

			std::swap_ranges(firstRow, firstRow + (ull)dimensions.second * pixelSize, secondRow);
		}
	}
}

void Image::rotate(RotationDirection direction) {

}
}