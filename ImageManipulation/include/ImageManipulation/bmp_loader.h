#ifndef BMP_IMAGE_LOADER
#define BMP_IMAGE_LOADER

#include "image.h"
#include <stdio.h>

Image* open_bmp_image(FILE* file);
void save_bmp_image(const Image* image, FILE* file);

#endif // BMP_IMAGE_LOADER
