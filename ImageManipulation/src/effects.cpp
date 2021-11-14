#include "pch.hpp"
#include <algorithm>
#include <execution>

namespace ImageManipulation {
void Image::invert() {
	std::for_each(std::execution::par_unseq, data.begin(), data.end(), [](auto& byte) {
		byte ^= 0xFF;
	});
}
}