#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

size_t countBasinSize(size_t row, size_t column, vector<string> const& buffer) {
	auto visited = make_unique<unique_ptr<bool[]>[]>(buffer.size());

	for(int i = 0; i < buffer.size(); ++i) {
		visited[i] = make_unique<bool[]>(buffer[0].size());
	}

	size_t size = 0;

	stack<pair<size_t, size_t>> s;
	s.push(make_pair(row, column));

	size_t i, j;

	do {
		tie(i, j) = s.top();
		s.pop();

		const char current = buffer[i][j];
		if(current == '9') {
			continue;
		}

		++size;

		if(i > 1 && !visited[i - 1][j] && buffer[i - 1][j] > current) {
			visited[i - 1][j] = true;
			s.push(make_pair(i - 1, j));
		}
		if(j > 1 && !visited[i][j - 1] && buffer[i][j - 1] > current) {
			visited[i][j - 1] = true;
			s.push(make_pair(i, j - 1));
		}
		if(i < buffer.size() - 2 && !visited[i + 1][j] && buffer[i + 1][j] > current) {
			visited[i + 1][j] = true;
			s.push(make_pair(i + 1, j));
		}
		if(j < buffer[0].size() - 2 && !visited[i][j + 1] && buffer[i][j + 1] > current) {
			visited[i][j + 1] = true;
			s.push(make_pair(i, j + 1));
		}

	} while(!s.empty());

	return size;
}

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

	priority_queue<size_t> pq;

	for(size_t row = 1; row < buffer.size() - 1; ++row) {
		for(size_t column = 1; column < buffer[0].size() - 1; ++column) {
			const char query = buffer[row][column];

			if(query < min({
				buffer[row + 1][column],
				buffer[row - 1][column],
				buffer[row][column + 1],
				buffer[row][column - 1]
				})) {
				pq.push(countBasinSize(row, column, buffer));
			}
		}
	}

	size_t risk = 1;

	for(int i = 0; i < 3; ++i) {
		risk *= pq.top();
		pq.pop();
	}

	cout << risk;

	return 0;
}
