#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char** argv) {
	int x = 0;
	int depth = 0;

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
		}
		else if(direction == "up") {
			depth -= length;
		}
		else if(direction == "down") {
			depth += length;
		}
		else assert(false);
	}

	cout << x * depth;
	
	return 0;
}