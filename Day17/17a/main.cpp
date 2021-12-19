#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;

int getMaxY(int yFrom) {
	assert(yFrom < 0);

	yFrom = -yFrom;
	return (yFrom * (yFrom - 1)) / 2;
}

int main(int argc, char** argv) {

	int xFrom, xTo, yFrom, yTo;

	int read = scanf("target area: x=%d..%d, y=%d..%d", &xFrom, &xTo, &yFrom, &yTo); // :(
	assert(read == 4);

	const int result = getMaxY(yFrom);

	cout << result << endl;

	return 0;
}
