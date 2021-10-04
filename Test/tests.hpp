#pragma once

#include <iostream>
#include <fstream>
#include <ImageManipulation/image.hpp>

void transformationsTest() {
	auto image = ImageManipulation::Image("res/image.bmp");

	image.flip(ImageManipulation::FlipDirection::HORIZONTAL);
	image.flip(ImageManipulation::FlipDirection::VERTICAL);
	//rotate_image(image, RotationDirection::LEFT);

	image.saveImage("res/image_test1.bmp");
}

void effectsTest() {
	auto image = ImageManipulation::Image("res/image.bmp");

	image.invert();

	image.saveImage("res/image_test2.bmp");
}