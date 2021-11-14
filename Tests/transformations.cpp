#include <CppUnitTest.h>
#include <ImageManipulation/image.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ImageManipulation {
TEST_CLASS(Transformations) {
private:
	Image* image;

	TEST_METHOD_INITIALIZE(Initialization) {
		image = new Image("res/image.bmp");
	}

	TEST_METHOD_CLEANUP(Cleaning) {
		delete image;
	}
public:
	TEST_METHOD(HorizontalFlip) {
		image->flip(FlipDirection::HORIZONTAL);

		image->saveImage("res/image_test1h.bmp");
	}

	TEST_METHOD(VerticalFlip) {
		image->flip(FlipDirection::VERTICAL);

		image->saveImage("res/image_test1v.bmp");
	}

	TEST_METHOD(Rotation) {
		image->rotate(RotationDirection::RIGHT);

		image->saveImage("res/image_test2.bmp");
	}
};
}