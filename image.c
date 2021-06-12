#include "image.h"
#include <stdlib.h>
#include <stdio.h>

static void swap(char* a, char* b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

static char* read_data(const Image* image) {
	fseek(image->file, sizeof(char) * image->header_size, SEEK_SET);

	char padding = (image->width * image->pixel_size) % 4;
	if(padding)
		padding = 4 - padding;

	unsigned int row_size = image->width * image->pixel_size;

	char* data = calloc(image->height * row_size, sizeof(char));

	if(!data)
		return NULL;

	for(unsigned int i = 0; i < image->height; i++) {
		fread(&data[i * row_size], sizeof(char), row_size, image->file);
		fseek(image->file, sizeof(char) * padding, SEEK_CUR);
	}

	return data;
}

static void write_data(const Image* image, const char* data) {
	fseek(image->file, sizeof(char) * image->header_size, SEEK_SET);

	char padding = (image->width * image->pixel_size) % 4;
	if(padding)
		padding = 4 - padding;

	unsigned int row_size = image->width * image->pixel_size;

	char zero = 0;

	for(unsigned int i = 0; i < image->height; i++) {
		fwrite(&data[i * row_size], sizeof(char), row_size, image->file);
		fwrite(&zero, sizeof(char), padding, image->file);
	}
}

static void copy_header(const Image* original_image, const Image* new_image) {
	rewind(original_image->file);
	rewind(new_image->file);

	char* header = calloc(original_image->header_size, sizeof(char));

	if(!header)
		return;

	fread(header, sizeof(char), original_image->header_size, original_image->file);
	fwrite(header, sizeof(char), new_image->header_size, new_image->file);

	free(header);
}

Image* alloc_image() {
	Image* image = (Image*)malloc(sizeof(Image));

	if(!image)
		return NULL;

	image->file = NULL;
	image->header_size = 0;

	image->width = 0;
	image->height = 0;
	image->pixel_size = 0;

	return image;
}

Image* open_image(const char path[]) {
	Image* image = alloc_image();

	image->file = fopen(path, "rb");

	fseek(image->file, 0x0A, SEEK_SET);
	fread(&image->header_size, sizeof(char) * 4, 1, image->file);

	fseek(image->file, 0x12, SEEK_SET);
	fread(&image->width, sizeof(char) * 4, 1, image->file);
	fread(&image->height, sizeof(char) * 4, 1, image->file);

	fseek(image->file, 0x1C, SEEK_SET);
	fread(&image->pixel_size, sizeof(char) * 2, 1, image->file);
	image->pixel_size &= 0xFFFF;
	image->pixel_size /= CHAR_BIT;

	return image;
}

void close_image(Image* image) {
	fclose(image->file);
	free(image);
}

Image* copy_image(const Image* original_image, const char path[]) {
	Image* new_image = alloc_image();

	new_image->file = fopen(path, "wb");
	new_image->header_size = original_image->header_size;

	new_image->width = original_image->width;
	new_image->height = original_image->height;
	new_image->pixel_size = original_image->pixel_size;

	copy_header(original_image, new_image);

	char* data = read_data(original_image);
	write_data(new_image, data);
	free(data);

	return new_image;
}

void invert_image(const Image* image) {
	char* data = read_data(image);

	unsigned int row_size = image->width * image->pixel_size;
	unsigned int half_width = image->width >> 1;

	for(unsigned int i = 0; i < image->height; i++)
		for(unsigned int j = 0; j < half_width; j++)
			for(unsigned int k = 0; k < image->pixel_size; k++) {
				int left = i * row_size + j * image->pixel_size + k;
				int right = (i + 1) * row_size - (j + 1) * image->pixel_size + k;

				swap(&data[left], &data[right]);
			}

	write_data(image, data);

	free(data);
}