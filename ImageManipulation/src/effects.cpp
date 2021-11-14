#include "pch.hpp"
#include <algorithm>

namespace ImageManipulation {
void Image::invert() {
	for(ull i = 0; i < (ull)dimensions.height * dimensions.width * pixelSize; i++)
		data[i] ^= 0xFF;
}
}