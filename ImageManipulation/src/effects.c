#include "pch.h"

typedef unsigned long long ull;

void invert_image(const Image* image) {
	for(ull i = 0; i < (ull)image->height * image->width * image->pixel_size; i++)
		image->data[i] ^= 0xFF;
}