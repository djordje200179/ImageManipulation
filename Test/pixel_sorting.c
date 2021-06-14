#include <ImageManipulation/image.h>
#include <ImageManipulation/bmp_loader.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int pixel_size = 0;
static int dir = -1;

char get_pixel_brightness(const Pixel pixel) {
	unsigned short sum = 0;
	for(unsigned int i = 0; i < pixel_size; i++)
		sum += pixel[i];

	return sum / pixel_size;
}

int pixel_comparision(const void* first_value, const void* second_value) {
	Pixel first_pixel = (Pixel)first_value;
	Pixel second_pixel = (Pixel)second_value;

	char first_brightness = get_pixel_brightness(first_pixel);
	char second_brightness = get_pixel_brightness(second_pixel);

	int result = 0;
	if(first_brightness > second_brightness)
		result = 1;
	else if(first_brightness < second_brightness)
		result = -1;
	else
		result = 0;

	return result * dir;
}

void pixel_sorting(const char original_image_path[], const char new_image_path[]) {
	FILE* input_file = fopen(original_image_path, "rb");

	Image* image = open_bmp_image(input_file);
	pixel_size = image->pixel_size;
	
	unsigned int parts = 5;
	unsigned int part_height = image->height / parts;
	for(unsigned int i = 0; i < parts; i++) {
		qsort(
			image->data + (i * part_height * image->width * image->pixel_size), 
			part_height * image->width, 
			image->pixel_size, 
			pixel_comparision
		);

		dir *= -1;
	}

	FILE* output_file = fopen(new_image_path, "wb");
	save_bmp_image(image, output_file);

	dealloc_image(image);
	fclose(output_file);
}