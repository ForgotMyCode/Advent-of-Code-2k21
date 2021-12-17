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

	constexpr size_t REPEATS = 5;

	const size_t originalColumnCount = matrix[0].size();

	for(size_t i = 0; i < matrix.size(); ++i) {
		for(size_t repeat = 1; repeat < REPEATS; ++repeat) {
			for(size_t j = 0; j < originalColumnCount; ++j) {
				matrix[i].push_back(1 + (matrix[i][matrix[i].size() - originalColumnCount] % 9));
			}
		}
	}

	const size_t originalRowCount = matrix.size();
	for(size_t repeat = 1; repeat < REPEATS; ++repeat) {
		for(size_t i = 0; i < originalRowCount; ++i) {
			matrix.push_back({});
			for(size_t j = 0; j < matrix[0].size(); ++j) {
				matrix[repeat * originalRowCount + i].push_back(1 + (matrix[matrix.size() - originalRowCount - 1][j] % 9));
			}
		}
	}

	AStarSolve<int> astar;
	int const pathLength = astar.GetShortestPath(matrix, 0, 0, matrix[0].size() - 1, matrix.size() - 1);

	cout << pathLength << endl;

	return 0;
}
