#include "pch.hpp"
#include <algorithm>
#include <execution>

namespace ImageManipulation {
void Image::flip(FlipDirection direction) {
	auto iterationHeight = dimensions.height >> (direction == FlipDirection::VERTICAL ? 1 : 0);;
	auto iterationWidth = dimensions.width >> (direction == FlipDirection::HORIZONTAL ? 1 : 0);

	if(direction == FlipDirection::HORIZONTAL) {
		for(ImageMetric i = 0; i < iterationHeight; i++) {
			for(ImageMetric j = 0; j < iterationWidth; j++) {
				Coordinates firstCoordinate { i, j };
				Coordinates secondCoordinate { i, dimensions.width - 1 - j };

				auto firstPixel = getPixelPointer(firstCoordinate);
				auto secondPixel = getPixelPointer(secondCoordinate);

				std::swap_ranges(std::execution::par_unseq, firstPixel, firstPixel + pixelSize, secondPixel);
			}
		}
	} else if(direction == FlipDirection::VERTICAL) {
		for(ImageMetric i = 0; i < iterationHeight; i++) {
			Coordinates firstCoordinate { i, 0 };
			Coordinates secondCoordinate { dimensions.height - 1 - i, 0 };

			auto firstRow = getPixelPointer(firstCoordinate);
			auto secondRow = getPixelPointer(secondCoordinate);

			std::swap_ranges(std::execution::par_unseq, firstRow, firstRow + (DataMetric)dimensions.width * pixelSize, secondRow);
		}
	}
}

void Image::rotate(RotationDirection direction) {
	throw "The function is not implemented yet.";
}
}