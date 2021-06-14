#include "pch.h"
#include <stdlib.h>
#include <string.h>

#define CHECK_PTR(pointer) if(!pointer) exit(1);

Image* alloc_image(const unsigned int width, const unsigned int height, const unsigned int pixel_size, const unsigned int header_size) {
	Image* image = (Image*)malloc(sizeof(Image));
	CHECK_PTR(image);

	image->width = width;
	image->height = height;
	image->pixel_size = pixel_size;

	image->data = (char*)calloc(height * width * pixel_size, sizeof(char));
	CHECK_PTR(image->data);

	image->header_size = header_size;
	image->header = (char*)calloc(header_size, sizeof(char));
	CHECK_PTR(image->header);

	return image;
}

void dealloc_image(Image* image) {
	free(image->data);
	free(image->header);
	free(image);
}

Image* duplicate_image(const Image* image) {
	Image* new_image = alloc_image(image->width, image->height, image->pixel_size, image->header_size);

	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < image->width; j++)
			memcpy(get_pixel(new_image, i, j), get_pixel(image, i, j), sizeof(char) * image->pixel_size);

	memcpy(new_image->header, image->header, sizeof(char) * image->header_size);

	return new_image;
}

char* get_pixel(const Image* image, const unsigned int i, const unsigned int j) {
	return &image->data[(i * image->width + j) * image->pixel_size];
}