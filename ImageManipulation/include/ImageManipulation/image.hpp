#pragma once

#include <vector>
#include <fstream>
#include <utility>

namespace ImageManipulation {
typedef unsigned long long ull;

typedef std::pair<ull, ull> Dimensions;
typedef std::pair<ull, ull> Coordinates;

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
	unsigned short pixelSize;

	std::vector<char> data;

	unsigned int headerSize;
	std::vector<char> header;

	void loadImage(std::ifstream& stream);
public:
	Image(Dimensions dimensions, unsigned short pixelSize, unsigned int headerSize);
	Image(std::ifstream& stream);
	Image(const char* filePath);

	std::vector<char>::const_iterator getPixel(Coordinates coordinate) const;
	std::vector<char>::iterator getPixel(Coordinates coordinate);

	Dimensions getDimensions() const;
	unsigned short getPixelSize() const;

	void saveImage(std::ofstream& stream) const;
	void saveImage(const char* filePath) const;

	void flip(FlipDirection direction);
	void rotate(RotationDirection direction);

	void invert();
};
}