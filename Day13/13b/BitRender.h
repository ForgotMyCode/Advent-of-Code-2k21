#pragma once

#include <limits>
#include <memory>
#include <ostream>

class BitRender {

public:
	BitRender(char const set, char const unset) : bits{ unset, set } {}

	template<typename Iter>
	void render(std::ostream& out, Iter const& begin, Iter const& end) const;

private:
	char bits[2];
};

template<typename Iter>
void BitRender::render(std::ostream& out, Iter const& begin, Iter const& end) const {
	int minX = std::numeric_limits<int>::max(),
		minY = std::numeric_limits<int>::max(),
		maxX = std::numeric_limits<int>::min(),
		maxY = std::numeric_limits<int>::min();

	for(auto it = begin; it != end; ++it) {
		auto const& point = *it;

		int const x = point[0];
		int const y = point[1];

		if(x < minX) {
			minX = x;
		}
		if(x > maxX) {
			maxX = x;
		}
		if(y < minY) {
			minY = y;
		}
		if(y > maxY) {
			maxY = y;
		}
	}

	const size_t bufferYsize = maxY + 1 - minY;
	const size_t bufferXsize = maxX + 1 - minX;

	std::unique_ptr<std::unique_ptr<char[]>[]> buffer(new std::unique_ptr<char[]>[bufferYsize]());
	for(size_t y = 0; y < bufferYsize; ++y) {
		buffer[y] = std::make_unique<char[]>(bufferXsize);
		for(size_t x = 0; x < bufferXsize; ++x) {
			buffer[y][x] = bits[0];
		}
	}

	for(auto it = begin; it != end; ++it) {
		auto const& point = *it;

		int const x = point[0] - minX;
		int const y = point[1] - minY;

		buffer[y][x] = bits[1];
	}

	for(size_t y = 0; y < bufferYsize; ++y) {
		for(size_t x = 0; x < bufferXsize; ++x) {
			out << buffer[y][x];
		}
		out << std::endl;
	}
}