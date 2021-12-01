#include <iostream>
#include <limits>
#include <queue>

using namespace std;

int main(int argc, char** argv) {
	constexpr int WINDOW_SIZE = 3;

	int lastWindow = numeric_limits<int>::max();
	int currentDepth;
	int currentWindow = 0;
	int totalIncreases = 0;
	queue<int> q;

	for(int i = 0; i < WINDOW_SIZE && cin.good(); ++i) {
		cin >> currentDepth;

		currentWindow += currentDepth;

		q.push(currentDepth);
	}

	while(cin.good()) {
		if(currentWindow > lastWindow) {
			++totalIncreases;
		}

		lastWindow = currentWindow;

		cin >> currentDepth;

		currentWindow += currentDepth - q.front();

		q.push(currentDepth);
		q.pop();
	}

	cout << totalIncreases;

	return 0;
}