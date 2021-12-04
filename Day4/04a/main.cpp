#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename T, size_t Columns, size_t Rows>
T sumBoardUnmarked(T (&board)[Columns][Rows], unordered_map<T, size_t> const& orderMap, size_t maxIndex) {
	T sum = T(0);
	
	for(size_t row = 0; row < Rows; ++row) {
		for(size_t column = 0; column < Columns; ++column) {
			T const& element = board[row][column];

			if(orderMap.at(element) > maxIndex) {
				sum += element;
			}
		}
	}

	return sum;
}

int main(int argc, char** argv) {

	constexpr size_t BOARD_SIZE = 5;

	unordered_map<int, size_t> orderMap;
	unordered_map<size_t, int> historyMap;

	{
		size_t time = 1;
		int number;
		char separator;
		string line;
		getline(cin, line);
		istringstream iss(line);

		do {
			iss >> number;
			iss >> separator;

			orderMap.insert(make_pair(number, time));
			historyMap.insert(make_pair(time, number));

			++time;
		} while(iss.good());
	}

	int boardBuffer[BOARD_SIZE][BOARD_SIZE];
	size_t columnOrderBuffer[BOARD_SIZE];

	size_t result = -1;

	{
		int number;
		size_t minTime = numeric_limits<size_t>::max();
		int board = 0;

		while(true) {
			++board;
			bool update = false;

			fill(columnOrderBuffer, columnOrderBuffer + BOARD_SIZE, numeric_limits<size_t>::min());

			for(size_t i = 0; i < BOARD_SIZE; ++i) {
				size_t rowOrder = numeric_limits<size_t>::min();

				for(size_t j = 0; j < BOARD_SIZE; ++j) {
					cin >> number;

					if(!cin.good()) {
						goto end;
					}

					boardBuffer[i][j] = number;
					
					const size_t order = orderMap.at(number);
					
					rowOrder = max(rowOrder, order);
					columnOrderBuffer[j] = max(columnOrderBuffer[j], order);
				}

				if(rowOrder < minTime) {
					minTime = rowOrder;
					update = true;
				}
			}

			const size_t bestColumnTime = *min_element(columnOrderBuffer, columnOrderBuffer + BOARD_SIZE);
			if(bestColumnTime < minTime) {
				minTime = bestColumnTime;
				update = true;
			}

			if(update) {
				result = sumBoardUnmarked<int>(boardBuffer, orderMap, minTime) * static_cast<size_t>(historyMap.at(minTime));
			}
		}
	}

end: {}

	cout << result << endl;

	return 0;
}
