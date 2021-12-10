#include <iostream>
#include <limits>
#include <stack>

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
			return 3;
		case ']':
			return 57;
		case '}':
			return 1197;
		case '>':
			return 25137;
	}

	throw exception("invalid bracket");
}

int main(int argc, char** agrv) {
	
	size_t score = 0;

	{
		stack<char> s;

		do {
			char c = (char) cin.get();

			if(!cin.good()) {
				break;
			}

			if(c == '\n') {
				// clear stack
				while(!s.empty()) s.pop();
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

					score += evaluateMissingBracket(c);

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

	cout << score << endl;
	
	return 0;
}
