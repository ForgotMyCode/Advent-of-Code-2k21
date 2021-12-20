#include <cassert>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#define NVERBOSE

class SnailfishNumber;

using SnailfishNumberReference = SnailfishNumber*;

class SnailfishNumber {
public:
	SnailfishNumber(int value) : 
		isRegularNumber(true),
		value(value) 
	{}

	SnailfishNumber(SnailfishNumber left, SnailfishNumber right) :
		isRegularNumber(false),
		left(new SnailfishNumber(left)),
		right(new SnailfishNumber(right))
	{
		this->left->SetParent(this, true);
		this->right->SetParent(this, false);
	}

	SnailfishNumber(SnailfishNumberReference left, SnailfishNumberReference right) :
		isRegularNumber(false),
		left(left),
		right(right)
	{
		this->left->SetParent(this, true);
		this->right->SetParent(this, false);
	}

	~SnailfishNumber() {
		if(!isRegularNumber) {
			delete left;
			delete right;
		}
	}

	SnailfishNumberReference GetLeft() const {
		return left;
	}

	SnailfishNumberReference GetRight() const {
		return right;
	}

	void SetLeft(SnailfishNumberReference number) {
		this->left = number;
		this->left->SetParent(this, true);
	}

	void SetRight(SnailfishNumberReference number) {
		this->right = number;
		this->right->SetParent(this, false);
	}

	void SetLeft(SnailfishNumber number) {
		SetLeft(new SnailfishNumber(number));
	}

	void SetRight(SnailfishNumber number) {
		SetRight(new SnailfishNumber(number));
	}


	void SetParent(SnailfishNumberReference parent, bool isLeft) {
		this->parent = parent;
		this->isLeft = isLeft;
	}

	void Explode() {
		// find first left
		{
			SnailfishNumberReference leftNode = this;
			while(leftNode != nullptr) {
				if(!leftNode->isLeft) {
					leftNode = leftNode->parent;
					break;
				}
				leftNode = leftNode->parent;
			}
			if(leftNode != nullptr) {
				leftNode = leftNode->left;

				while(!leftNode->isRegularNumber) {
					leftNode = leftNode->right;
				}
			}

			if(leftNode != nullptr) {
				assert(left);
				leftNode->value += left->value;
			}
		}

		// find first right
		{
			SnailfishNumberReference rightNode = this;
			while(rightNode != nullptr) {
				if(rightNode->isLeft) {
					rightNode = rightNode->parent;
					break;
				}
				rightNode = rightNode->parent;
			}
			if(rightNode != nullptr) {
				rightNode = rightNode->right;

				while(!rightNode->isRegularNumber) {
					rightNode = rightNode->left;
				}
			}

			if(rightNode != nullptr) {
				assert(right);
				rightNode->value += right->value;
			}
		}

		assert(this->parent);
		if(isLeft) {
			this->parent->SetLeft(SnailfishNumber{ 0 });
		}
		else {
			this->parent->SetRight(SnailfishNumber{ 0 });
		}

		delete this;
	}

	SnailfishNumberReference Split() {
		assert(this->parent);

		SnailfishNumberReference newNumber = new SnailfishNumber(this->value / 2, (this->value + 1) / 2);

		if(isLeft) {
			this->parent->SetLeft(newNumber);
		}
		else {
			this->parent->SetRight(newNumber);
		}

		delete this;

		return newNumber;
	}

	bool SanitizeExplode(int depth = 0) {
		if(depth == 4 && !isRegularNumber) {
			#ifdef VERBOSE
			cout << "Explode " << *this << endl;
			#endif
			Explode();
			return true;
		}
		if(!isRegularNumber) {
			return left->SanitizeExplode(depth + 1) || right->SanitizeExplode(depth + 1);
		}
		return false;
	}

	bool SanitizeSplit() {
		if(isRegularNumber && value >= 10) {
			#ifdef VERBOSE
			cout << "Split " << *this << endl;
			#endif
			SnailfishNumberReference newNode = Split();
			/*
			if(depth == 4) {
				#ifdef VERBOSE
				cout << "Immediately Explode " << *newNode << endl;
				#endif
				newNode->Explode();
			}
			*/
			return true;
		}
		if(!isRegularNumber) {
			return left->SanitizeSplit() || right->SanitizeSplit();
		}
		return false;
	}

	bool Sanitize(int depth = 0) {
		if(SanitizeExplode()) {
			return true;
		}
		if(SanitizeSplit()) {
			return true;
		}
		return false;
	}

	SnailfishNumberReference Add(SnailfishNumberReference rhs) {
		SnailfishNumberReference root = new SnailfishNumber(this, rhs);
		#ifdef VERBOSE
		cout << ">" << * root << endl;
		#endif
		while(root->Sanitize()) {
			#ifdef VERBOSE
			cout << "..." << *root << endl;
			#endif
		}
		return root;
	}

	long Magnitude() {
		if(isRegularNumber) {
			return value;
		}
		// else
		return 3 * left->Magnitude() + 2 * right->Magnitude();
	}

	SnailfishNumberReference Clone() {
		SnailfishNumberReference ret = isRegularNumber ?
			new SnailfishNumber(value) :
			new SnailfishNumber(left->Clone(), right->Clone());

		ret->isRegularNumber = isRegularNumber;
		ret->isLeft = isLeft;
		ret->parent = parent;

		return ret;
	}

private:
	bool isRegularNumber;
	bool isLeft = true;
	SnailfishNumberReference parent = nullptr;
	union {
		int value;
		struct {
			SnailfishNumberReference left, right;
		};
	};

	friend ostream& operator<<(ostream& os, SnailfishNumber const& number);
};

ostream& operator<<(ostream& os, SnailfishNumber const& number) {
	if(number.isRegularNumber) {
		os << number.value;
	}
	else {
		os << '[' << * number.left << "," << *number.right << ']';
	}

	return os;
}

SnailfishNumberReference parseSnailFishNumber(string const& in) {
	stack<SnailfishNumberReference> s;

	for(int i = 0; i < in.length(); ++i) {
		char const c = in[i];
		if(c == '[' || c == ',') {
			continue;
		}
		if(c == ']') {
			assert(s.size() >= 2);

			SnailfishNumberReference right = s.top();
			s.pop();
			SnailfishNumberReference left = s.top();
			s.pop();

			s.push(new SnailfishNumber(left, right));

			continue;
		}
		int buffer = 0;
		while(in[i] >= '0' && in[i] <= '9') {
			buffer = buffer * 10 + (in[i] - '0');
			++i;
		}
		--i;
		s.push(new SnailfishNumber(buffer));
	}


	assert(s.size() == 1);

	return s.top();
}

#ifndef TESTING
int main(int argc, char** argv) {

	vector<SnailfishNumberReference> numbers;

	do {
		string in;

		getline(cin, in);

		if(!cin.good()) {
			break;
		}

		numbers.push_back(parseSnailFishNumber(in));

	} while(true);

	long maxMagnitude = numeric_limits<long>::min();

	for(int i = 0; i < numbers.size(); ++i) {
		for(int j = 0; j < numbers.size(); ++j) {
			if(i == j) {
				continue;
			}
			SnailfishNumberReference a = numbers[i]->Clone();
			SnailfishNumberReference b = numbers[j]->Clone();

			SnailfishNumberReference sum = a->Add(b);
			long magnitude = sum->Magnitude();

			maxMagnitude = max(maxMagnitude, magnitude);
			delete sum;
		}
	}

	cout << maxMagnitude << endl;

	for(auto n : numbers) {
		delete n;
	}

	return 0;
}
#endif