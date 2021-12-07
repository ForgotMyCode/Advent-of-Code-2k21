#include <iostream>
#include <limits>
#include <vector>

using namespace std;

#ifndef MIN_POSITION
#define MIN_POSITION 0
#endif

#ifndef MAX_POSITION
#define MAX_POSITION 2000
#endif

int main(int argc, char** argv) {
	vector<int> positions;

	{
		int in;
		char sep;

		do {
			cin >> in;
			if(!cin.good()) {
				break;
			}
			cin >> sep;

			positions.push_back(in);
		} while(true);
	}

	int bestFuelCost = numeric_limits<int>::max();

	for(int query = MIN_POSITION; query <= MAX_POSITION; ++query) {
		int fuelCost = 0;

		for(int idxTarget = 0; idxTarget < positions.size(); ++idxTarget) {
			const int distance = abs(positions[idxTarget] - query);
			fuelCost += distance * (distance + 1) / 2;
		}

		if(fuelCost < bestFuelCost) {
			bestFuelCost = fuelCost;
		}
	}

	cout << bestFuelCost << endl;

	return 0;
}