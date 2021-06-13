#include "image_bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline static void check_ptr(const void* pointer) {
	if(!pointer) {
		printf("MEMORY_ERROR");
		exit(0);
	}
}

inline static void swap(char* ptr_a[], char* ptr_b[]) {
	char* temp = *ptr_a;
	*ptr_a = *ptr_b;
	*ptr_b = temp;
}

ImageBMP* alloc_image(const unsigned int width, const unsigned int height, const unsigned int pixel_size, const unsigned int header_size) {
	ImageBMP* image = (ImageBMP*)malloc(sizeof(ImageBMP));
	check_ptr(image);

	image->width = width;
	image->height = height;
	image->pixel_size = pixel_size;

	image->data = (char***)calloc(height, sizeof(char**));
	check_ptr(image->data);
	for(unsigned int i = 0; i < height; i++) {
		image->data[i] = (char**)calloc(width, sizeof(char*));
		check_ptr(image->data[i]);

		for(unsigned int j = 0; j < width; j++) {
			image->data[i][j] = (char*)calloc(pixel_size, sizeof(char));
			check_ptr(image->data[i][j]);
		}
	}

	image->header_size = header_size;
	image->header = (char*)calloc(header_size, sizeof(char));
	check_ptr(image->header);

	return image;
}

void dealloc_image(ImageBMP* image) {
	for(unsigned int i = 0; i < image->height; i++) {
		for(unsigned int j = 0; j < image->width; j++)
			free(image->data[i][j]);
		free(image->data[i]);
	}
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

	for(unsigned int i = 0; i < height; i++) {
		for(unsigned int j = 0; j < width; j++)
			fread(image->data[i][j], sizeof(char), pixel_size, file);
		
		fseek(file, sizeof(char) * padding, SEEK_CUR);
	}

	return image;
}

ImageBMP* duplicate_image(const ImageBMP* image) {
	ImageBMP* new_image = alloc_image(image->width, image->height, image->pixel_size, image->header_size);

	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < image->width; j++)
			memcpy(new_image->data[i][j], image->data[i][j], sizeof(char) * image->pixel_size);

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
			fwrite(image->data[i][j], sizeof(char), image->pixel_size, file);

		fwrite(&zero, sizeof(char), padding, file);
	}
}

void flip_horizontally_image(ImageBMP* image) {
	unsigned int half_width = image->width >> 1;

	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < half_width; j++)
			swap(&image->data[i][j], &image->data[i][image->width - 1 - j]);
}

void flip_vertically_image(ImageBMP* image) {
	unsigned int half_height = image->height >> 1;

	for(unsigned int i = 0; i < half_height; i++)
		for(unsigned int j = 0; j < image->width; j++)
			swap(&image->data[i][j], &image->data[image->height - 1 - i][j]);
}

void invert_image(ImageBMP* image) {
	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < image->width; j++)
			for(unsigned int k = 0; k < image->pixel_size; k++)
				image->data[i][j][k] = ~image->data[i][j][k];
}