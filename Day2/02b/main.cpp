#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char** argv) {
	int x = 0;
	int depth = 0;
	int aim = 0;

	string direction;
	int length;

	while(true) {
		cin >> direction;
		cin >> length;

		if(!cin.good()) {
			break;
		}

		if(direction == "forward") {
			x += length;
			depth += aim * length;
		}
		else if(direction == "up") {
			aim -= length;
		}
		else if(direction == "down") {
			aim += length;
		}
		else assert(false);
	}

	cout << x * depth;
	
	return 0;
}