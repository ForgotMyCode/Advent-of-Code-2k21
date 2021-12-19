#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;

int getMinValocity(int from) {
	assert(from > 1);

	int base = int(sqrt(from - 1));
	base += base % 2 == 0 ? 1 : 2;

	int const result = (base - 1) / 2;

	return result;
}

bool isHitWithVelocity(int velocityX, int velocityY, int xFrom, int xTo, int yFrom, int yTo) {
	int positionX = 0;
	int positionY = 0;

	for(int currentVelocityX = velocityX, currentVelocityY = velocityY; ; --currentVelocityY) {
		if(positionX > xTo) {
			return false;
		}
		if(positionY < yFrom) {
			return false;
		}
		if(positionX >= xFrom && positionY <= yTo) {
			return true;
		}

		positionX += currentVelocityX;
		positionY += currentVelocityY;

		if(currentVelocityX > 0) {
			--currentVelocityX;
		}
	}
	return false;
}

size_t getPossibleVelocities(int xFrom, int xTo, int yFrom, int yTo) {
	size_t possibleVelocities = 0;

	for(int velocityX = getMinValocity(xFrom); velocityX <= xTo; ++velocityX) {
		for(int velocityY = yFrom; velocityY <= -yFrom; ++velocityY) {
			if(isHitWithVelocity(velocityX, velocityY, xFrom, xTo, yFrom, yTo)) {
				++possibleVelocities;
			}
		}
	}

	return possibleVelocities;
}

int main(int argc, char** argv) {

	int xFrom, xTo, yFrom, yTo;

	int read = scanf("target area: x=%d..%d, y=%d..%d", &xFrom, &xTo, &yFrom, &yTo); // :(
	assert(read == 4);

	const size_t result = getPossibleVelocities(xFrom, xTo, yFrom, yTo);

	cout << result << endl;

	return 0;
}
