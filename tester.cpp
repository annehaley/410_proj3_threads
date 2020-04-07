#include "tester.h"
#include "print_ts.h"
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

vector<thread> vec;
bool flag = true;
void threadManager(std::string &txt, WHICH_PRINT wp,
		int numTimesToPrint, int ms_delay){
	for(int j=0; j<numTimesToPrint; j++){
		if (flag) {
			switch(wp){
			case P2:
				PRINT2(txt,txt);
				this_thread::sleep_for(chrono::milliseconds(ms_delay));
				break;
			case P3:
				PRINT3(txt,txt,txt);
				this_thread::sleep_for(chrono::milliseconds(ms_delay));
				break;
			case P4:
				PRINT4(txt,txt,txt,txt);
				this_thread::sleep_for(chrono::milliseconds(ms_delay));
				break;
			case P5:
				PRINT5(txt,txt,txt,txt,txt);
				this_thread::sleep_for(chrono::milliseconds(ms_delay));
				break;
			default:
				PRINT1(txt);
				this_thread::sleep_for(chrono::milliseconds(ms_delay));
			}
		}
	}
}

void startThreads(
		std::string s, int numThreads, WHICH_PRINT wp,
		int numTimesToPrint, int millisecond_delay){

	for (int i = 0; i < numThreads; ++i) {
		vec.push_back(thread(threadManager, ref(s),
				wp, numTimesToPrint, millisecond_delay));
	}

}

void setCancelThreads(bool bCancel){
	if (bCancel){
		for(int i = 0; i<vec.size(); i++){
			std::string s = USER_CHOSE_TO_CANCEL;
			PRINT1(s);
		}
		flag = false;
	}
}

void joinThreads(){
	for(auto &t: vec){
		t.join();
	}
}
