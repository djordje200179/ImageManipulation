#include <stdio.h>
#include <ImageManipulation/bmp_loader.h>
#include <ImageManipulation/image.h>
#include <ImageManipulation/transformations.h>

void transformations_test() {
	printf("TEST: Transformations\n");

	FILE* input_file = fopen("res/image.bmp", "rb");
	Image* image = open_bmp_image(input_file);
	fclose(input_file);

	flip_image(image, VERTICAL);
	flip_image(image, HORIZONTAL);

	FILE* output_file = fopen("res/image_test1.bmp", "wb");
	save_bmp_image(image, output_file);
	fclose(output_file);

	dealloc_image(image);
}