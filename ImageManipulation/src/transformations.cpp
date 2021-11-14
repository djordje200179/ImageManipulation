#include "pch.hpp"
#include <algorithm>

namespace ImageManipulation {
void Image::flip(FlipDirection direction) {
	auto iterationHeight = dimensions.height >> (direction == FlipDirection::VERTICAL ? 1 : 0);;
	auto iterationWidth = dimensions.width >> (direction == FlipDirection::HORIZONTAL ? 1 : 0);

	if(direction == FlipDirection::HORIZONTAL) {
		for(ImageMetric i = 0; i < iterationHeight; i++) {
			for(ImageMetric j = 0; j < iterationWidth; j++) {
				Coordinates firstCoordinate { i, j };
				Coordinates secondCoordinate { i, dimensions.width - 1 - j };

				auto firstRow = getPixel(firstCoordinate);
				auto secondRow = getPixel(secondCoordinate);

				std::swap_ranges(firstRow, firstRow + pixelSize, secondRow);
			}
		}
	} else if(direction == FlipDirection::VERTICAL) {
		for(ImageMetric i = 0; i < iterationHeight; i++) {
			Coordinates firstCoordinate { i, 0 };
			Coordinates secondCoordinate { dimensions.height - 1 - i, 0 };

			auto firstRow = getPixel(firstCoordinate);
			auto secondRow = getPixel(secondCoordinate);

			std::swap_ranges(firstRow, firstRow + (DataMetric)dimensions.width * pixelSize, secondRow);
		}
	}
}

void Image::rotate(RotationDirection direction) {

}
}