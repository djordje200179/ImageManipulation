#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

Image* open_bmp_image(FILE* file) {
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

	Image* image = alloc_image(width, height, pixel_size, header_size);
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

void save_bmp_image(const Image* image, FILE* file) {
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