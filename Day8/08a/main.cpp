#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

vector<string> split(string str, string const& delim) {
	vector<string> ret;

	size_t pos;
	while((pos = str.find(delim)) != string::npos) {
		ret.push_back(str.substr(0, pos));
		str = str.substr(pos + delim.length(), string::npos);
	}
	ret.push_back(str);

	return ret;
}

int main(int argc, char** argv) {
	
	int appearances = 0;

	{
		string in;
		
		do {
			getline(cin, in);

			if(!cin.good()) {
				break;
			}

			vector<string> inputOutput = split(in, " | ");
			assert(inputOutput.size() == 2);

			vector<string> outputNums = split(inputOutput[1], " ");

			for(string const& number : outputNums) {
				switch(number.length()) {
					case 2:
					case 3:
					case 4:
					case 7:
						++appearances;
						break;
				}
			}

		} while(true);

		cout << appearances << endl;
	}

	return 0;
}
