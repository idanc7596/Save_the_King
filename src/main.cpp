#include <cstdlib>
#include <time.h>
#include "Controller.h"

int main() {
	
	srand(unsigned(time(NULL))); //for randomization
	Controller controller;
	controller.run();

	return EXIT_SUCCESS;
}