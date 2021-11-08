#include <CppUnitTest.h>
#include <ImageManipulation/image.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ImageManipulation {
TEST_CLASS(Transformations) {
public:
	TEST_METHOD(Flip) {
		Image image("res/image.bmp");

		image.flip(FlipDirection::HORIZONTAL);
		image.flip(FlipDirection::VERTICAL);

		image.saveImage("res/image_test1.bmp");
	}

	TEST_METHOD(Rotation) {
		Image image("res/image.bmp");

		image.rotate(RotationDirection::RIGHT);

		image.saveImage("res/image_test2.bmp");
	}
};
}