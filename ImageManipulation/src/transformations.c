#include "pch.h"

inline static void swap_char(char* a, char* b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

inline static void swap_pixels(Pixel a, Pixel b, const unsigned int pixel_size) {
	for(unsigned int i = 0; i < pixel_size; i++)
		swap_char(&a[i], &b[i]);
}

void flip_horizontally_image(const Image* image) {
	unsigned int half_width = image->width >> 1;

	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < half_width; j++) {
			Pixel first_pixel = get_pixel(image, i, j);
			Pixel second_pixel = get_pixel(image, i, image->width - 1 - j);

			swap_pixels(first_pixel, second_pixel, image->pixel_size);
		}
}

void flip_vertically_image(const Image* image) {
	unsigned int half_height = image->height >> 1;

	for(unsigned int i = 0; i < half_height; i++)
		for(unsigned int j = 0; j < image->width; j++) {
			Pixel first_pixel = get_pixel(image, i, j);
			Pixel second_pixel = get_pixel(image, image->height - 1 - i, j);

			swap_pixels(first_pixel, second_pixel, image->pixel_size);
		}
}