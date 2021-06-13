#ifndef IMAGE
#define IMAGE

#include <stdio.h>

typedef struct ImageBMP {
	unsigned int width, height;
	unsigned int pixel_size;

	char*** data;

	unsigned int header_size;
	char* header;
} ImageBMP;

ImageBMP* alloc_image(const unsigned int width, const unsigned int height, const unsigned int pixel_size, const unsigned int header_size);
void dealloc_image(ImageBMP* image);

ImageBMP* open_image(FILE* file);
ImageBMP* duplicate_image(const ImageBMP* image);
void save_image(const ImageBMP* image, FILE* file);

void flip_horizontally_image(ImageBMP* image);
void flip_vertically_image(ImageBMP* image);
void invert_image(ImageBMP* image);

#endif // IMAGE