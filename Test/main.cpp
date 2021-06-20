#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "tests.hpp"

int main() {
	transformations_test();

	_CrtDumpMemoryLeaks();

	return 0;
}
