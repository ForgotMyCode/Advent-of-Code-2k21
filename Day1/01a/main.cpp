#include <iostream>
#include <limits>

using namespace std;

int main(int argc, char** argv) {

	int lastDepth = numeric_limits<int>::max();
	int currentDepth;
	int totalIncreases = 0;

	cin >> currentDepth;
	while(cin.good()) {
		if(currentDepth > lastDepth) {
			++totalIncreases;
		}

		lastDepth = currentDepth;

		cin >> currentDepth;
	}

	cout << totalIncreases;

	return 0;
}