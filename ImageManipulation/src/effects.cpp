#include "pch.hpp"
#include <algorithm>

namespace ImageManipulation {
	void Image::invert() {
		for(auto& byte : data) {
			byte ^= 0xFF;
		}
	}
}