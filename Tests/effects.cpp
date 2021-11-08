#include <CppUnitTest.h>
#include <ImageManipulation/image.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ImageManipulation {
TEST_CLASS(Effects) {
public:
	TEST_METHOD(Invert) {
		Image image("res/image.bmp");

		image.invert();

		image.saveImage("res/image_test3.bmp");
	}
};
}