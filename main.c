#include "image.h"

int main() {
	Image* original_image = open_image("image.bmp");
	Image* new_image = copy_image(original_image, "image_inv.bmp");

	invert_image(new_image);

	close_image(original_image);
	close_image(new_image);

	return 0;
}
