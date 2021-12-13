#include <cassert>
#include <iostream>
#include <omp.h>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "Point.h"

using namespace std;

pair<string, string> pairSplit(string const& str, string const& delim) {
	size_t position = str.find(delim);
	string a = str.substr(0, position);
	string b = str.substr(position + delim.length());
	return make_pair(a, b);
}

int main(int argc, char** argv) {

	vector<Point<int, 2>> points;

	{
		string in;
		string x, y;

		do {
			getline(cin, in);

			assert(cin.good());

			if(in.length() == 0) {
				break;
			}

			tie(x, y) = pairSplit(in, ",");

			points.push_back({ stoi(x), stoi(y) });

		} while(true);
	}

	{
		string in;
		string lhs, rhs;

		do {
			getline(cin, in);

			if(!cin.good()) {
				break;
			}

			tie(lhs, rhs) = pairSplit(in, "=");

			bool const foldByX = lhs[lhs.length() - 1] == 'x';
			int const foldAt = stoi(rhs);
			
			if(foldByX) {
				#pragma omp parallel for
				for(int i = 0; i < points.size(); ++i) {
					auto& point = points[i];
					if(point[0] > foldAt) {
						point[0] = 2 * foldAt - point[0];
					}
				}
			}
			else {
				assert(lhs[lhs.length() - 1] == 'y');

				#pragma omp parallel for
				for(int i = 0; i < points.size(); ++i) {
					auto& point = points[i];
					if(point[1] > foldAt) {
						point[1] = 2 * foldAt - point[1];
					}
				}
			}

		} while(false);
	}

	unordered_set<Point<int, 2>> uniquePoints(points.begin(), points.end());
	cout << uniquePoints.size() << endl;

	return 0;
	
}
