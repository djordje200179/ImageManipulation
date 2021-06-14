#include "pch.h"

inline static void swap_char(char* a, char* b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

inline static void swap_array(char* a, char* b, const unsigned int length) {
	for(unsigned int i = 0; i < length; i++)
		swap_char(&a[i], &b[i]);
}

void flip_horizontally_image(Image* image) {
	unsigned int half_width = image->width >> 1;

	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < half_width; j++) {
			char* first_pixel = get_pixel(image, i, j);
			char* second_pixel = get_pixel(image, i, image->width - 1 - j);

			swap_array(first_pixel, second_pixel, image->pixel_size);
		}
}

void flip_vertically_image(Image* image) {
	unsigned int half_height = image->height >> 1;

	for(unsigned int i = 0; i < half_height; i++)
		for(unsigned int j = 0; j < image->width; j++) {
			char* first_pixel = get_pixel(image, i, j);
			char* second_pixel = get_pixel(image, image->height - 1 - i, j);

			swap_array(first_pixel, second_pixel, image->pixel_size);
		}
}