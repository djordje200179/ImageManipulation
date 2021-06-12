#ifndef IMAGE
#define IMAGE

#include <stdio.h>

typedef struct Image {
	FILE* file;
	unsigned int header_size;

	unsigned int width, height;
	unsigned int pixel_size;
} Image;

Image* alloc_image();
Image* open_image(const char path[]);
void close_image(Image* image);

Image* copy_image(const Image* original_image, const char path[]);

void invert_image(const Image* image);

#endif // IMAGE