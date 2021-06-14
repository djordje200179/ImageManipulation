#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include "tests.h"

int main() {
	basic_operations("res/image.bmp", "res/image_inv.bmp");
	printf("Test 1 completed\n");

	pixel_sorting("res/image.bmp", "res/image_sort.bmp");
	printf("Test 2 completed\n");

	_CrtDumpMemoryLeaks();

	return 0;
}
