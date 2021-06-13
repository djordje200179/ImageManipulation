#include "image_bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_PTR(pointer)      \
	if(!pointer) {              \
		printf("MEMORY_ERROR"); \
		exit(0);				\
	}							\

inline static void swap_char(char* a, char* b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

inline static void swap_array(char* a, char* b, const unsigned int length) {
	for(unsigned int i = 0; i < length; i++)
		swap_char(&a[i], &b[i]);
}

ImageBMP* alloc_image(const unsigned int width, const unsigned int height, const unsigned int pixel_size, const unsigned int header_size) {
	ImageBMP* image = (ImageBMP*)malloc(sizeof(ImageBMP));
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

void dealloc_image(ImageBMP* image) {
	free(image->data);
	free(image->header);
	free(image);
}

ImageBMP* open_image(FILE* file) {
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int pixel_size = 0;
	unsigned int header_size = 0;

	fseek(file, 0x0A, SEEK_SET);
	fread(&header_size, sizeof(char) * 4, 1, file);

	fseek(file, 0x12, SEEK_SET);
	fread(&width, sizeof(char) * 4, 1, file);
	fread(&height, sizeof(char) * 4, 1, file);

	fseek(file, 0x1C, SEEK_SET);
	fread(&pixel_size, sizeof(char) * 2, 1, file);
	pixel_size &= 0xFFFF;
	pixel_size /= CHAR_BIT;

	ImageBMP* image = alloc_image(width, height, pixel_size, header_size);
	rewind(file);
	fread(image->header, sizeof(char), header_size, file);

	char padding = (image->width * image->pixel_size) % 4;
	if(padding)
		padding = 4 - padding;

	for(unsigned int i = 0; i < image->height; i++) {
		for(unsigned int j = 0; j < image->width; j++)
			fread(get_pixel(image, i, j), sizeof(char), pixel_size, file);

		fseek(file, sizeof(char) * padding, SEEK_CUR);
	}

	return image;
}

ImageBMP* duplicate_image(const ImageBMP* image) {
	ImageBMP* new_image = alloc_image(image->width, image->height, image->pixel_size, image->header_size);

	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < image->width; j++)
			memcpy(get_pixel(new_image, i, j), get_pixel(image, i, j), sizeof(char) * image->pixel_size);

	memcpy(new_image->header, image->header, sizeof(char) * image->header_size);

	return new_image;
}

void save_image(const ImageBMP* image, FILE* file) {
	rewind(file);

	fwrite(image->header, sizeof(char), image->header_size, file);

	char padding = (image->width * image->pixel_size) % 4;
	if(padding)
		padding = 4 - padding;

	int zero = 0;
	for(unsigned int i = 0; i < image->height; i++) {
		for(unsigned int j = 0; j < image->width; j++)
			fwrite(get_pixel(image, i, j), sizeof(char), image->pixel_size, file);

		fwrite(&zero, sizeof(char), padding, file);
	}
}

void flip_horizontally_image(ImageBMP* image) {
	unsigned int half_width = image->width >> 1;

	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < half_width; j++) {
			char* first_pixel = get_pixel(image, i, j);
			char* second_pixel = get_pixel(image, i, image->width - 1 - j);

			swap_array(first_pixel, second_pixel, image->pixel_size);
		}
}

void flip_vertically_image(ImageBMP* image) {
	unsigned int half_height = image->height >> 1;

	for(unsigned int i = 0; i < half_height; i++)
		for(unsigned int j = 0; j < image->width; j++) {
			char* first_pixel = get_pixel(image, i, j);
			char* second_pixel = get_pixel(image, image->height - 1 - i, j);

			swap_array(first_pixel, second_pixel, image->pixel_size);
		}
}

void invert_image(ImageBMP* image) {
	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < image->width; j++) {
			char* pixel = get_pixel(image, i, j);

			for(unsigned int k = 0; k < image->pixel_size; k++)
				pixel[k] = ~pixel[k];
		}
}

char* get_pixel(const ImageBMP* image, const unsigned int i, const unsigned int j) {
	return &image->data[(i * image->width + j) * image->pixel_size];
}