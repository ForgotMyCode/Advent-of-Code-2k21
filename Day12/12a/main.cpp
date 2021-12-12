#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#include "Graph.h"

using namespace std;

size_t nameToIdx(string const& name) {
	static unordered_map<string, size_t> nameMap;

	auto search = nameMap.find(name);

	if(search != nameMap.end()) {
		return search->second;
	}

	const size_t index = nameMap.size();
	nameMap.insert(make_pair(name, index));

	return index;
}

pair<string, string> pairSplit(string const& str, string const& delim) {
	size_t position = str.find(delim);
	string a = str.substr(0, position);
	string b = str.substr(position + delim.length());
	return make_pair(a, b);
}

int main(int argc, char** argv) {

	Graph g;

	{
		string in, from, to;
		do {

			getline(cin, in);

			if(!cin.good()) {
				break;
			}

			tie(from, to) = pairSplit(in, "-");

			g.AddEdge(nameToIdx(from), islower(from[0]), nameToIdx(to), islower(to[0]));
		} while(true);

	}

	const size_t start = nameToIdx("start");
	const size_t end = nameToIdx("end");

	size_t result = g.FindPaths(start, end);

	cout << result << endl;

	return 0;
}
