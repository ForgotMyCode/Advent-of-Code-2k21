#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "astar.h"

using namespace std;

vector<int> parseString(string const& str) {
	vector<int> ret;

	for(char c : str) {
		assert(c >= '0' && c <= '9');
		ret.push_back(c - '0');
	}

	return ret;
}

int main(int argc, char** argv) {

	vector<vector<int>> matrix;

	{
		string in;

		do {
			getline(cin, in);

			if(!cin.good()) {
				break;
			}

			matrix.push_back(parseString(in));

		} while(true);
	}

	AStarSolve<int> astar;
	int const pathLength = astar.GetShortestPath(matrix, 0, 0, matrix[0].size() - 1, matrix.size() - 1);

	cout << pathLength << endl;

	return 0;
}
