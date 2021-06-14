#include "pch.h"

void invert_image(const Image* image) {
	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < image->width; j++) {
			Pixel pixel = get_pixel(image, i, j);

			for(unsigned int k = 0; k < image->pixel_size; k++)
				pixel[k] = ~pixel[k];
		}
}