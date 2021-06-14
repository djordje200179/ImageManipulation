#ifndef IMAGE
#define IMAGE

typedef struct Image {
	unsigned int width, height;
	unsigned int pixel_size;

	char* data;

	unsigned int header_size;
	char* header;
} Image;

typedef char* Pixel;

Image* alloc_image(const unsigned int width, const unsigned int height, const unsigned int pixel_size, const unsigned int header_size);
void dealloc_image(Image* image);

Image* duplicate_image(const Image* image);

Pixel get_pixel(const Image* image, const unsigned int i, const unsigned int j);
void set_pixel(const Image* image, const unsigned int i, const unsigned int j, const Pixel value);

#endif // IMAGE