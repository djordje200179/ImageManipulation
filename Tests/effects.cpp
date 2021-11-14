#include <CppUnitTest.h>
#include <ImageManipulation/image.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ImageManipulation {
TEST_CLASS(Effects) {
private:
	Image* image;
public:
	TEST_METHOD_INITIALIZE(Initialization) {
		image = new Image("res/image.bmp");
	}

	TEST_METHOD_CLEANUP(Cleaning) {
		delete image;
	}

	TEST_METHOD(Invert) {
		image->invert();

		image->saveImage("res/image_test3.bmp");
	}
};
}