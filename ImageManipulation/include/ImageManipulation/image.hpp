#pragma once

#include <vector>
#include <fstream>
#include <utility>

namespace ImageManipulation {
	typedef unsigned long long ull;

	typedef std::pair<unsigned int, unsigned int> Dimensions;
	typedef std::pair<unsigned int, unsigned int> Coordinates;

	enum class FlipDirection {
		NONE = 0,
		HORIZONTAL = 1,
		VERTICAL = 2,
		BOTH = 3
	};

	enum class RotationDirection {
		LEFT,
		RIGHT
	};

	class Image {
	private:
		Dimensions dimensions;
		unsigned short pixel_size;

		std::vector<char> data;

		unsigned int header_size;
		std::vector<char> header;

		void load_image(std::ifstream& stream);
	public:
		Image(Dimensions dimensions, unsigned short pixel_size, unsigned int header_size);
		Image(std::ifstream& stream);
		Image(const char* file_path);

		std::vector<char>::iterator get_pixel(Coordinates coordinate);

		Dimensions get_dimensions() const;
		unsigned short get_pixel_size() const;

		void save_image(std::ofstream& stream);
		void save_image(const char* file_path);

		void flip(FlipDirection direction);
		void rotate(RotationDirection direction);

		void invert();
	};
}