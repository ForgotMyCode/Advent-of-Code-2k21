#include <cassert>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

void countOnesInString(string const& str, unique_ptr<size_t[]> const& buffer) {
	for(size_t i = 0; i < str.length(); ++i) {
		if(str[i] == '1') {
			++buffer[i];
		}
		else assert(str[i] == '0');
	}
}

int main(int argc, char** argv) {
	string in;
	size_t count = 0;

	cin >> in;
	assert(cin.good());

	const size_t bits = in.length();

	unique_ptr<size_t[]> ones = make_unique<size_t[]>(bits);

	while(cin.good()) {
		++count;
		countOnesInString(in, ones);

		cin >> in;
	}

	size_t const bound = count / 2;

	size_t mostCommonBits = 0;
	size_t leastCommonBits = 0;

	size_t mask = 1;
	for(int i = bits - 1; i >= 0; --i, mask <<= 1) {
		if(ones[i] > bound) {
			// ones are most common bits
			mostCommonBits |= mask;
		}
		else {
			// ones are least common bits
			leastCommonBits |= mask;
		}
	}

	cout << mostCommonBits * leastCommonBits << endl;
	
	return 0;
}