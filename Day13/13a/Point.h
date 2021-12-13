#pragma once
#include <array>
#include <functional>

template<typename T, size_t dim>
struct Point {

	template<typename... S>
	Point(S... args) : buffer{ args... } {}

	inline
	T& operator[](size_t index) {
		return buffer[index];
	}

	inline
	T const& operator[](size_t index) const {
		return buffer[index];
	}

	inline
	bool operator==(Point const& other) const {
		for(size_t i = 0; i < dim; ++i) {
			if(buffer[i] != other[i]) {
				return false;
			}
		}
		return true;
	}

private:
	T buffer[dim];
};

template<typename T, size_t dim>
struct std::hash<Point<T, dim>> {

	inline
	size_t operator()(Point<T, dim> const& object) const {
		size_t hash = 0;
		for(size_t i = 0; i < dim; ++i) {
			hash ^= std::hash<T>()(object[i]);
		}
		return hash;
	}
};