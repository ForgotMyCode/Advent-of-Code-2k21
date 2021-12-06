#include <iostream>
#include <cstdint>

using num = int64_t;

using namespace std;

#ifndef DAYS
#define DAYS 256
#endif

constexpr int cycleLength = 7;
constexpr int initialLength = 9;

num SPAWNS[DAYS + 1];

int main(int argc, char** argv) {

	for(num i = DAYS + 1; i >= 0; --i) {
		num sum = 0;

		for(num j = i + 1; j < DAYS + 1; j += cycleLength) {
			if(j + initialLength - 1 < DAYS + 1) {
				sum += SPAWNS[j + initialLength - 1];
			}
			++sum;
		}

		SPAWNS[i] = sum;
	}

	num remaining;
	char separator;

	num totalFish = 0;

	do {
		cin >> remaining;
		
		if(!cin.good()) {
			break;
		}

		cin >> separator;

		++totalFish;
		if(remaining <= DAYS) {
			totalFish += SPAWNS[remaining];
		}
	} while(true);

	cout << totalFish << endl;

	return 0;
}