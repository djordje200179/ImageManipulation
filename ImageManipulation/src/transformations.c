#include "pch.h"
#include <string.h>
#include <stdlib.h>

static void swap_pixels(const Image* image, const unsigned int i0, const unsigned int j0, const unsigned i1, const unsigned int j1) {
	Pixel first_pixel = get_pixel(image, i0, j0);
	Pixel second_pixel = get_pixel(image, i1, j1);

	Pixel temp_pixel = (char*)calloc(image->pixel_size, 1);
	if(!temp_pixel)
		exit(1);

	memcpy(temp_pixel, first_pixel, image->pixel_size);

	set_pixel(image, i0, j0, second_pixel);
	set_pixel(image, i1, j1, temp_pixel);

	free(temp_pixel);
}

void flip_horizontally_image(const Image* image) {
	unsigned int half_width = image->width >> 1;

	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < half_width; j++)
			swap_pixels(image, i, j, i, image->width - 1 - j);
}

void flip_vertically_image(const Image* image) {
	unsigned int half_height = image->height >> 1;

	for(unsigned int i = 0; i < half_height; i++)
		for(unsigned int j = 0; j < image->width; j++)
			swap_pixels(image, i, j, image->height - 1 - i, j);
}

void invert_image(const Image* image) {
	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < image->width; j++) {
			Pixel pixel = get_pixel(image, i, j);

			for(unsigned int k = 0; k < image->pixel_size; k++)
				pixel[k] = ~pixel[k];
		}
}

void rotate_image(const Image* image) {

}