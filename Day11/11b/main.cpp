#include <array>
#include <iostream>
#include <limits>
#include <stack>
#include <tuple>

using namespace std;

template<typename T, size_t Rows, size_t Columns>
class Matrix {
public:
	inline
	T const& Get(size_t const x, size_t const y) {
		return buffer[y * Columns + x];
	}

	inline
	void Set(size_t const x, size_t const y, T const& value) {
		buffer[y * Columns + x] = value;
	}

	inline
	void Increment(size_t const x, size_t const y) {
		++buffer[y * Columns + x];
	}

private:
	T buffer[Rows * Columns] = {T(0)};
};

template<size_t Size>
class OctopusSimulation {
public:
	OctopusSimulation(array<array<int, Size>, Size> initialState) {
		for(size_t i = 0; i < Size; ++i) {
			for(size_t j = 0; j < Size; ++j) {
				buffer.Set(j, i, initialState[i][j]);
			}
		}
	}

	size_t Step() {
		IncrementEnergy();
		size_t ret = SpreadLight();
		Normalize();

		return ret;
	}

private:
	void IncrementEnergy() {
		for(size_t i = 0; i < Size; ++i) {
			for(size_t j = 0; j < Size; ++j) {
				buffer.Increment(j, i);
			}
		}
	}

	size_t SpreadLight() {
		stack<pair<size_t, size_t>> s;

		for(size_t i = 0; i < Size; ++i) {
			for(size_t j = 0; j < Size; ++j) {
				if(buffer.Get(j, i) == 10) {
					s.push(make_pair(j, i));
				}
			}
		}

		size_t ret = 0;

		size_t x, y;

		while(!s.empty()) {
			++ret;

			tie(x, y) = s.top();
			s.pop();

			if(x > 0) {
				if(buffer.Get(x - 1, y) == 9) {
					s.push(make_pair(x - 1, y));
				}
				buffer.Increment(x - 1, y);

				if(y > 0) {
					if(buffer.Get(x - 1, y - 1) == 9) {
						s.push(make_pair(x - 1, y - 1));
					}
					buffer.Increment(x - 1, y - 1);					
				}

				if(y < Size - 1) {
					if(buffer.Get(x - 1, y + 1) == 9) {
						s.push(make_pair(x - 1, y + 1));
					}
					buffer.Increment(x - 1, y + 1);
				}
			}

			if(y > 0) {
				if(buffer.Get(x, y - 1) == 9) {
					s.push(make_pair(x, y - 1));
				}
				buffer.Increment(x, y - 1);
			}

			if(x < Size - 1) {
				if(buffer.Get(x + 1, y) == 9) {
					s.push(make_pair(x + 1, y));
				}
				buffer.Increment(x + 1, y);

				if(y > 0) {
					if(buffer.Get(x + 1, y - 1) == 9) {
						s.push(make_pair(x + 1, y - 1));
					}
					buffer.Increment(x + 1, y - 1);
				}

				if(y < Size - 1) {
					if(buffer.Get(x + 1, y + 1) == 9) {
						s.push(make_pair(x + 1, y + 1));
					}
					buffer.Increment(x + 1, y + 1);
				}
			}

			if(y < Size - 1) {
				if(buffer.Get(x, y + 1) == 9) {
					s.push(make_pair(x, y + 1));
				}
				buffer.Increment(x, y + 1);
			}
		}

		return ret;
	}

	void Normalize() {
		for(size_t i = 0; i < Size; ++i) {
			for(size_t j = 0; j < Size; ++j) {
				if(buffer.Get(j, i) > 9) {
					buffer.Set(j, i, 0);
				}
			}
		}
	}


	Matrix<int, Size, Size> buffer;
};

int main(int argc, char** argv) {
	array<array<int, 10>, 10> arr;

	char n;

	for(int i = 0; i < 10; ++i) {
		for(int j = 0; j < 10; ++j) {
			cin >> n;
			arr[i][j] = n - '0';
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	OctopusSimulation<10> simulation(arr);
	size_t result = -1;

	for(int step = 1; ; ++step) {
		if(simulation.Step() == 100) {
			result = step;
			break;
		}
	}

	cout << result << endl;

	return 0;
}
