#include <algorithm>
#include <iostream>
#include <limits>
#include <stack>
#include <vector>

using namespace std;

char getMatchingBracket(char bracket) {
	switch(bracket) {
		case '(':
			return ')';
		case '[':
			return ']';
		case '{':
			return '}';
		case '<':
			return '>';
	}

	throw exception("invalid bracket");
}

bool isOpeningBracket(char bracket) {
	switch(bracket) {
		case '(':
		case '[':
		case '{':
		case '<':
			return true;
	}
	return false;
}

size_t evaluateMissingBracket(char bracket) {
	switch(bracket) {
		case ')':
			return 1;
		case ']':
			return 2;
		case '}':
			return 3;
		case '>':
			return 4;
	}

	throw exception("invalid bracket");
}

int main(int argc, char** agrv) {
	
	vector<size_t> scores;

	{
		stack<char> s;

		vector<char> history;
		do {
			char c = (char) cin.get();
			history.push_back(c);

			if(!cin.good()) {
				break;
			}

			if(c == '\n') {
				if(!s.empty()) {
					size_t score = 0;

					while(!s.empty()) {
						score = 5 * score + evaluateMissingBracket(s.top());
						s.pop();
					}

					scores.push_back(score);
				}

				continue;
			}

			if(isOpeningBracket(c)) {
				s.push(getMatchingBracket(c));
			}
			else {
				// closing bracket
				if(s.empty() || s.top() != c) {

					// clear stack
					while(!s.empty()) s.pop();

					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					continue;
				}
				else {
					// ok
					s.pop();
				}
			}

		} while(true);
	}

	sort(scores.begin(), scores.end());

	cout << scores[scores.size() / 2] << endl;
	
	return 0;
}
