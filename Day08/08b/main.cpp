#include <bitset>
#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

using byte = unsigned char;

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

size_t bitCount(byte b) {
	return bitset<7>(b).count();
}

byte parseByte(string const& str) {
	byte ret = 0;

	for(char c : str) {
		ret |= 1 << (c - 'a');
	}

	return ret;
}

unordered_map<byte, int> createDecoder(vector<string> const& digits) {
	assert(digits.size() == 10);

	unordered_map<byte, int> decoderMap;

	vector<byte> bytesOfLength[8];

	for(string const& digit : digits) {
		bytesOfLength[digit.length()].push_back(parseByte(digit));
	}

	// obtain the unique digits
	// 1
	assert(bytesOfLength[2].size() == 1);
	const byte one = bytesOfLength[2][0];
	decoderMap.insert(make_pair(one, 1));

	// 4
	assert(bytesOfLength[4].size() == 1);
	const byte four = bytesOfLength[4][0];
	decoderMap.insert(make_pair(four, 4));

	// 7
	assert(bytesOfLength[3].size() == 1);
	const byte seven = bytesOfLength[3][0];
	decoderMap.insert(make_pair(seven, 7));

	// 8
	assert(bytesOfLength[7].size() == 1);
	decoderMap.insert(make_pair(bytesOfLength[7][0], 8));

	// 3
	byte three;
	for(byte const query : bytesOfLength[5]) {
		if(bitCount(query & one) == 2) {
			three = query;
			decoderMap.insert(make_pair(three, 3));
			break;
		}
	}

	// 6 and 9
	byte zero, six, nine;

	for(byte const query : bytesOfLength[6]) {
		if(bitCount(query & one) == 1) {
			six = query;
			decoderMap.insert(make_pair(six, 6));
		}

		if(bitCount(query & four) == 4) {
			nine = query;
			decoderMap.insert(make_pair(nine, 9));
		}
	}

	// 0
	for(byte const query : bytesOfLength[6]) {
		if(query != six && query != nine) {
			zero = query;
			decoderMap.insert(make_pair(zero, 0));
			break;
		}
	}

	// 2 and 5
	byte two, five;
	for(byte const query : bytesOfLength[5]) {
		if(bitCount(query & six) == 5) {
			five = query;
		}
		if(bitCount(query & nine) == 4) {
			two = query;
		}
	}
	decoderMap.insert(make_pair(two, 2));
	decoderMap.insert(make_pair(five, 5));

	return decoderMap;
}

int decode(string const& query, unordered_map<byte, int> const& decoderMap) {
	byte queryByte = parseByte(query);
	
	auto entry = decoderMap.find(queryByte);
	assert(entry != decoderMap.end());

	return entry->second;
}

int main(int argc, char** argv) {
	
	long sum = 0;

	{
		string in;
		
		do {
			getline(cin, in);

			if(!cin.good()) {
				break;
			}

			vector<string> inputOutput = split(in, " | ");
			assert(inputOutput.size() == 2);

			vector<string> inputNums = split(inputOutput[0], " ");
			vector<string> outputNums = split(inputOutput[1], " ");

			auto decoderMap = createDecoder(inputNums);

			long number = 0;

			for(string const& strDigit : outputNums) {
				number = (10 * number) + decode(strDigit, decoderMap);
			}

			sum += number;

		} while(true);

		cout << sum << endl;
	}

	return 0;
}
