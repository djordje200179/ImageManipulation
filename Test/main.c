#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <ImageManipulation/bmp_loader.h>
#include <ImageManipulation/image.h>
#include <ImageManipulation/manipulator.h>

int main() {
	FILE* input_file = fopen("res/image.bmp", "rb");
	FILE* output_file = fopen("res/image_out.bmp", "wb");
	printf("DEBUG: Files loaded\n");

	Image* original_image = open_bmp_image(input_file);
	printf("DEBUG: Image loaded\n");

	Image* new_image = duplicate_image(original_image);
	printf("DEBUG: Image duplicated\n");

	flip_horizontally_image(new_image);
	flip_vertically_image(new_image);
	invert_image(new_image);
	printf("DEBUG: Image edited\n");

	save_bmp_image(new_image, output_file);
	printf("DEBUG: Image saved\n");

	dealloc_image(original_image);
	dealloc_image(new_image);
	printf("DEBUG: Images deallocated\n");

	fclose(input_file);
	fclose(output_file);
	printf("DEBUG: Files closed\n");

	_CrtDumpMemoryLeaks();

	return 0;
}
