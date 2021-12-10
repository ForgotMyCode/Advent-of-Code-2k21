#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {

	vector<string> buffer;

	{
		string in;

		do {
			cin >> in;
			if(!cin.good()) {
				break;
			}

			buffer.push_back("9" + in + "9");

		} while(true);
	}

	buffer.insert(buffer.begin(), string(buffer[0].length(), '9'));
	buffer.push_back(string(buffer[0].length(), '9'));

	size_t risk = 0;

	for(size_t row = 1; row < buffer.size() - 1; ++row) {
		for(size_t column = 1; column < buffer[0].size() - 1; ++column) {
			const char query = buffer[row][column];

			if(query < min({
				buffer[row + 1][column],
				buffer[row - 1][column],
				buffer[row][column + 1],
				buffer[row][column - 1]
				})) {
				risk += 1 + size_t(query - '0');
			}
		}
	}

	cout << risk;

	return 0;
}
