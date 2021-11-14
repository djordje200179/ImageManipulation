#include <CppUnitTest.h>
#include <ImageManipulation/image.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ImageManipulation {
TEST_CLASS(Transformations) {
public:
	TEST_METHOD(HorizontalFlip) {
		Image image("res/image.bmp");

		image.flip(FlipDirection::HORIZONTAL);

		image.saveImage("res/image_test1h.bmp");
	}

	TEST_METHOD(VerticalFlip) {
		Image image("res/image.bmp");

		image.flip(FlipDirection::VERTICAL);

		image.saveImage("res/image_test1v.bmp");
	}

	TEST_METHOD(Rotation) {
		Image image("res/image.bmp");

		image.rotate(RotationDirection::RIGHT);

		image.saveImage("res/image_test2.bmp");
	}
};
}