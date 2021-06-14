#include "pch.h"

#define SWAP(x, y) { int t = x; x = y; y = t; }

inline static void swap_pixels(Pixel a, Pixel b, const unsigned int pixel_size) {
	for(unsigned int i = 0; i < pixel_size; i++)
		SWAP(a[i], b[i]);
}

void flip_image(const Image* image, const FlipDirection direction) {
	unsigned int height = image->height >> (direction == VERTICAL);
	unsigned int width = image->width >> (direction == HORIZONTAL);

	for(unsigned int i = 0; i < height; i++)
		for(unsigned int j = 0; j < width; j++) {
			Pixel first_pixel = get_pixel(image, i, j);

			Pixel second_pixel = get_pixel(image, 
										   direction == VERTICAL ? image->height - 1 - i : i,
										   direction == HORIZONTAL ? image->width - 1 - j : j);

			swap_pixels(first_pixel, second_pixel, image->pixel_size);
		}
}