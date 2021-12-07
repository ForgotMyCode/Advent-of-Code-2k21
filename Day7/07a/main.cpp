#include <iostream>
#include <limits>
#include <vector>

using namespace std;

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

	for(int idxTarget = 0; idxTarget < positions.size(); ++idxTarget) {
		int fuelCost = 0;

		for(int idxQuery = 0; idxQuery < positions.size(); ++idxQuery) {
			fuelCost += abs(positions[idxTarget] - positions[idxQuery]);
		}

		if(fuelCost < bestFuelCost) {
			bestFuelCost = fuelCost;
		}
	}

	cout << bestFuelCost << endl;

	return 0;
}