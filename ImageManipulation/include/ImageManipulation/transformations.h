#ifndef TRANSFORMATIONS
#define TRANSFORMATIONS

#include "image.h"

typedef enum FlipDirection {
	HORIZONTAL = 1, VERTICAL = 2
} FlipDirection;

typedef enum RotationDirection {
	LEFT, RIGHT
} RotationDirection;

void flip_image(const Image* image, const FlipDirection direction);
void rotate_image(Image* image, const RotationDirection direction);

#endif // TRANSFORMATIONS