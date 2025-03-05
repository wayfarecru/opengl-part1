#ifndef __cplusplus
#error This file works only with C++
#endif

#include <chrono>
#include <stdio.h>
#include <thread> // for sleep_for()
using namespace std;
using namespace std::chrono;

int main(void) {
    system_clock::time_point lastTime = system_clock::now();
	std::this_thread::sleep_for( std::chrono::milliseconds(100) );
    system_clock::time_point curTime = system_clock::now();
	milliseconds duration = duration_cast<milliseconds>(curTime - lastTime);
    printf("%lld milli-seconds\n", duration.count());
	return 0;
}

