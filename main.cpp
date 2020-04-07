#include "tester.h"
#include "print_ts.h"
#include <iostream>

using namespace std;
int main(){
	std::string s = "s";
	int numThreads = 4;
	WHICH_PRINT wp = P5;
	int numTimesToPrint = 6;
	int millisecond_delay = 1000;


	startThreads(s, numThreads, wp, numTimesToPrint, millisecond_delay);

	joinThreads();

}
