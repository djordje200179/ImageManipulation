#include "pch.h"
#include <algorithm>

namespace ImageManipulation {
	void Image::invert() {
		std::transform(data.begin(), data.end(), data.begin(), [](char c) {
			return ~c;
		});
	}
}