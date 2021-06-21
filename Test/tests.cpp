#include <iostream>
#include <fstream>
#include <ImageManipulation/image.hpp>

void transformations_test() {
	std::cout << "TEST: Transformations" << std::endl;

	auto image = ImageManipulation::Image("res/image.bmp");

	image.flip(ImageManipulation::FlipDirection::HORIZONTAL);
	image.flip(ImageManipulation::FlipDirection::VERTICAL);
	//rotate_image(image, RotationDirection::LEFT);

	image.save_image("res/image_test1.bmp");
}

void effects_test() {
	std::cout << "TEST: Effects" << std::endl;

	auto image = ImageManipulation::Image("res/image.bmp");

	image.invert();

	image.save_image("res/image_test2.bmp");
}