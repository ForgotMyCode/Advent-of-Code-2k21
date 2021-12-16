#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#ifndef STEPS
#define STEPS 40
#endif

using namespace std;

using Rules = unordered_map<string, string>;
using Statistics = unordered_map<char, size_t>;

class PairwiseStatistics {

public:
	PairwiseStatistics(string const& word, Rules const& rules) : rules(rules) {
		assert(word.length() > 0);

		for(size_t i = 0; i < word.length() - 1; ++i) {
			incrementValue(word.substr(i, 2));
		}
	}

	PairwiseStatistics(Rules const& rules) : rules(rules) {}

	PairwiseStatistics step() {
		PairwiseStatistics nextStatistics(rules);

		for(auto const& entry : currentStatistics) {
			if(entry.second.hasValidRule) {
				nextStatistics.incrementValue(string(1, entry.first[0]) + entry.second.ruleTo, entry.second.count);
				nextStatistics.incrementValue(entry.second.ruleTo + string(1, entry.first[1]), entry.second.count);
			}
			else {
				nextStatistics.incrementValue(entry.first, entry.second.count);
			}
		}

		return nextStatistics;
	}

	Statistics generateStatistics() {
		Statistics statistics;

		for(auto const& entry : currentStatistics) {
			char const statisticsQuery = entry.first[1];

			auto statisticsSearch = statistics.find(statisticsQuery);

			if(statisticsSearch != statistics.end()) {
				statisticsSearch->second += entry.second.count;
			}
			else {
				statistics.insert({ statisticsQuery, entry.second.count });
			}
		}

		return statistics;
	}

private:
	struct Value {
		size_t count;
		bool hasValidRule;
		string ruleTo;
	};

	void incrementValue(string const& key, size_t amount = 1) {
		auto search = currentStatistics.find(key);

		if(search != currentStatistics.end()) {
			(search->second.count) += amount;
		}
		else {
			auto ruleSearch = rules.find(key);

			if(ruleSearch != rules.end()) {
				currentStatistics.insert({ key, {amount, true, ruleSearch->second } });
			}
			else {
				currentStatistics.insert({ key, {amount, false, ""} });
			}
		}
	}

	unordered_map<string, Value> currentStatistics;
	Rules rules;
};

pair<pair<char, size_t>, pair<char, size_t>> getLeastAndMostCommonCharacter(Statistics const& statistics) {
	char leastCommonCharacter = '\0';
	size_t minCount = numeric_limits<size_t>::max();
	char mostCommonCharacter = '\0';
	size_t maxCount = numeric_limits<size_t>::min();

	for(auto const& entry : statistics) {
		if(entry.second > maxCount) {
			mostCommonCharacter = entry.first;
			maxCount = entry.second;
		}
		if(entry.second < minCount) {
			leastCommonCharacter = entry.first;
			minCount = entry.second;
		}
	}

	return make_pair(make_pair(leastCommonCharacter, minCount), make_pair(mostCommonCharacter, maxCount));
}

pair<string, string> pairSplit(string const& str, string const& delim) {
	size_t position = str.find(delim);
	string a = str.substr(0, position);
	string b = str.substr(position + delim.length());
	return make_pair(a, b);
}

int main(int argc, char** argv) {
	string word;
	// read first line
	getline(cin, word);
	Rules rules;

	{
		string in;
		string ruleLhs, ruleRhs;

		// skip 1 line
		getline(cin, in);

		do {
			getline(cin, in);
			if(!cin.good()) {
				break;
			}

			tie(ruleLhs, ruleRhs) = pairSplit(in, " -> ");

			rules.insert(make_pair(ruleLhs, ruleRhs));

		} while(true);
	}

	const char firstLetter = word[0];

	PairwiseStatistics pairwiseStatistics(word, rules);
	for(size_t step = 1; step <= STEPS; ++step) {
		pairwiseStatistics = pairwiseStatistics.step();
	}

	auto statistics = pairwiseStatistics.generateStatistics();

	{
		auto search = statistics.find(firstLetter);

		if(search != statistics.end()) {
			++(search->second);
		}
		else {
			statistics.insert({ firstLetter, 1 });
		}
	}

	auto commonCharacters = getLeastAndMostCommonCharacter(statistics);

	const size_t mostCommonCharCount = commonCharacters.second.second;
	const size_t leastCommonCharCount = commonCharacters.first.second;

	cout << (mostCommonCharCount - leastCommonCharCount) << endl;

	return 0;
}
