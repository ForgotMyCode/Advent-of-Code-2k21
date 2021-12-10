#include <iostream>
#include <string>
#include <tuple>

using namespace std;

constexpr size_t MAX_SIZE = 1000;
constexpr char NOT_TAKEN = '\0';
constexpr char TAKEN = 'T';
constexpr char COLLIDED = 'C';

char BUFFER[MAX_SIZE][MAX_SIZE] = { { NOT_TAKEN } };

pair<string, string> split(string const& str, string const& delim) {
	size_t const delimeterPosition = str.find(delim);

	string left = str.substr(0, delimeterPosition);
	string right = str.substr(delimeterPosition + delim.length(), string::npos);

	return make_pair(left, right);
}

size_t fillAndReportCollisions(int xFrom, int yFrom, int xTo, int yTo) {
	size_t ret = 0;

	if(xFrom == xTo) {
		for(int y = min(yFrom, yTo); y <= max(yFrom, yTo); ++y) {
			if(BUFFER[y][xFrom] == NOT_TAKEN) {
				BUFFER[y][xFrom] = TAKEN;
			}
			else if(BUFFER[y][xFrom] == TAKEN) {
				BUFFER[y][xFrom] = COLLIDED;
				++ret;
			}
		}
	}
	else if(yFrom == yTo) {
		for(int x = min(xFrom, xTo); x <= max(xFrom, xTo); ++x) {
			if(BUFFER[yFrom][x] == NOT_TAKEN) {
				BUFFER[yFrom][x] = TAKEN;
			}
			else if(BUFFER[yFrom][x] == TAKEN) {
				BUFFER[yFrom][x] = COLLIDED;
				++ret;
			}
		}
	}

	return ret;
}

int main(int argc, char** argv) {
	string in, left, right, leftX, rightX, leftY, rightY;
	string const delim1 = " -> ", delim2 = ",";

	size_t collisions = 0;

	do {
		getline(cin, in);
		if(!cin.good()) {
			break;
		}

		tie(left, right) = split(in, delim1);
		tie(leftX, leftY) = split(left, delim2);
		tie(rightX, rightY) = split(right, delim2);

		collisions += fillAndReportCollisions(stoi(leftX), stoi(leftY), stoi(rightX), stoi(rightY));
	} while(true);

	cout << collisions << endl;
}