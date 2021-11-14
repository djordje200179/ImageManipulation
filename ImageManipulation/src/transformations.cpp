#include "pch.hpp"
#include <algorithm>

namespace ImageManipulation {
void Image::flip(FlipDirection direction) {
	auto iterationHeight = dimensions.height >> (direction == FlipDirection::VERTICAL ? 1 : 0);;
	auto iterationWidth = dimensions.width >> (direction == FlipDirection::HORIZONTAL ? 1 : 0);

	if(direction == FlipDirection::HORIZONTAL) {
		for(auto i = 0u; i < iterationHeight; i++) {
			for(auto j = 0u; j < iterationWidth; j++) {
				Coordinates firstCoordinate { i, j };
				Coordinates secondCoordinate { i, dimensions.width - 1 - j };

				auto firstRow = getPixel(firstCoordinate);
				auto secondRow = getPixel(secondCoordinate);

				std::swap_ranges(firstRow, firstRow + pixelSize, secondRow);
			}
		}
	} else if(direction == FlipDirection::VERTICAL) {
		for(auto i = 0u; i < iterationHeight; i++) {
			Coordinates firstCoordinate { i, 0 };
			Coordinates secondCoordinate { dimensions.height - 1 - i, 0 };

			auto firstRow = getPixel(firstCoordinate);
			auto secondRow = getPixel(secondCoordinate);

			std::swap_ranges(firstRow, firstRow + (ull)dimensions.width * pixelSize, secondRow);
		}
	}
}

void Image::rotate(RotationDirection direction) {

}
}