#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "tests.hpp"
#include "test.hpp"

int main() {
	Test("Transformations", transformationsTest).test();
	Test("Effects", transformationsTest).test();

	_CrtDumpMemoryLeaks();

	return 0;
}