#include "pch.hpp"
#include <algorithm>

namespace ImageManipulation {
void Image::invert() {
	for(ull i = 0; i < getDataSize(); i++)
		data[i] ^= 0xFF;
}
}