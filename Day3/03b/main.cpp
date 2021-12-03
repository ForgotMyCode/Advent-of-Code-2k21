#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

template<typename T>
void verboseBinaryCountingSort(T* arr, size_t from, size_t to, size_t index, size_t& split, bool& isZeroMostCommon) {
	size_t zeros = 0;
	size_t ones = 0;

	for(size_t i = from; i < to; ++i) {
		if(arr[i][index] == '0') {
			++zeros;
		}
		else {
			++ones;
		}
	}

	split = from + zeros;
	isZeroMostCommon = zeros > ones;

	size_t onesIndex = from + zeros;

	for(size_t i = from; i < from + zeros; ) {
		if(arr[i][index] == '0') {
			++i;
		}
		else {
			swap(arr[i], arr[onesIndex]);
			++onesIndex;
		}
	}
}

int main(int argc, char** argv) {
	string in;

	vector<string> strings;

	while(true) {
		cin >> in;

		if(!cin.good()) {
			break;
		}

		strings.push_back(in);
	}

	const size_t length = strings[0].length();

	size_t splitOxygen, fromOxygen, toOxygen, splitCO2, fromCO2, toCO2;
	bool isZeroMostCommonOxygen;
	bool isZeroMostCommonCO2;

	// using oxygen's variables just as auxiliary fields
	verboseBinaryCountingSort(strings.data(), 0, strings.size(), 0, splitOxygen, isZeroMostCommonOxygen);

	if(isZeroMostCommonOxygen) {
		fromOxygen = 0;
		toOxygen = splitOxygen;
		fromCO2 = splitOxygen;
		toCO2 = strings.size();
	}
	else {
		fromOxygen = splitOxygen;
		toOxygen = strings.size();
		fromCO2 = 0;
		toCO2 = splitOxygen;
	}

	string oxygenRating;
	string CO2Rating;

	// resolve oxygen
	for(size_t i = 1; i < length + 1; ++i) {
		if(toOxygen - fromOxygen == 1) {
			oxygenRating = strings[fromOxygen];
			break;
		}
		assert(i < length);

		verboseBinaryCountingSort(strings.data(), fromOxygen, toOxygen, i, splitOxygen, isZeroMostCommonOxygen);
		
		if(isZeroMostCommonOxygen) {
			toOxygen = splitOxygen;
		}
		else {
			fromOxygen = splitOxygen;
		}
	}

	// resolve CO2
	for(size_t i = 1; i < length + 1; ++i) {
		if(toCO2 - fromCO2 == 1) {
			CO2Rating = strings[fromCO2];
			break;
		}
		assert(i < length);

		verboseBinaryCountingSort(strings.data(), fromCO2, toCO2, i, splitCO2, isZeroMostCommonCO2);

		if(isZeroMostCommonCO2) {
			fromCO2 = splitCO2;
		}
		else {
			toCO2 = splitCO2;
		}
	}

	cout << stoi(oxygenRating, nullptr, 2) * stoi(CO2Rating, nullptr, 2) << endl;
	
	return 0;
}