#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "tests.h"

int main() {
	transformations_test();

	_CrtDumpMemoryLeaks();

	return 0;
}
