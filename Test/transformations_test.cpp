#include <iostream>
#include <fstream>
#include <ImageManipulation/image.hpp>

void transformations_test() {
	std::cout << "TEST: Transformations" << std::endl;

	ImageManipulation::Image image("res/image.bmp");
	
	image.flip(ImageManipulation::FlipDirection::HORIZONTAL);
	image.flip(ImageManipulation::FlipDirection::VERTICAL);
	//rotate_image(image, RotationDirection::LEFT);
	
	image.save_image("res/image_test1.bmp");
}