#include <ImageManipulation/image.h>
#include <ImageManipulation/bmp_loader.h>
#include <ImageManipulation/transformations.h>
#include <ImageManipulation/effects.h>
#include <stdio.h>
#include <stdlib.h>

void basic_operations(const char original_image_path[], const char new_image_path[]) {
	FILE* input_file = fopen(original_image_path, "rb");

	Image* image = open_bmp_image(input_file);
	flip_horizontally_image(image);
	flip_vertically_image(image);
	invert_image(image);

	FILE* output_file = fopen(new_image_path, "wb");
	save_bmp_image(image, output_file);

	dealloc_image(image);
	fclose(output_file);
}