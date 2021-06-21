#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "tests.hpp"
#include "test.hpp"

int main() {
	Test("Transformations", transformations_test).test();
	Test("Effects", transformations_test).test();

	_CrtDumpMemoryLeaks();

	return 0;
}