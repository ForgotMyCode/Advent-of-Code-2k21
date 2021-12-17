#pragma once

#include <limits>
#include <vector>
#include <set>

template<typename T>
class AStarSolve {

public:
	int GetShortestPath(std::vector<std::vector<T>> inputMatrix, int startX, int startY, int goalX, int goalY);

protected:
	static const T INF = std::numeric_limits<T>::max();

	struct AStarPivot {
		int x, y;
		T g;
		std::vector<AStarPivot*> neighbours;
	};

	static T ManhattanDistance(int x1, int y1, int x2, int y2);

	T h(AStarPivot const& pivot) const;

	T f(AStarPivot const& pivot) const;

	bool Solve();
	
	std::vector<std::vector<T>> Input;
	std::vector<std::vector<std::pair<size_t, size_t>>> Previous;
	std::vector<std::vector<AStarPivot>> Pivots;
	int StartX, StartY, GoalX, GoalY;
};

template<typename T>
T AStarSolve<T>::ManhattanDistance(int x1, int y1, int x2, int y2) {
	if(x1 > x2) {
		std::swap(x1, x2);
	}
	if(y1 > y2) {
		std::swap(y1, y2);
	}
	return T(x2 - x1 + y2 - y1);
}

template<typename T>
T AStarSolve<T>::h(AStarPivot const& pivot) const {
	return ManhattanDistance(pivot.x, pivot.y, GoalX, GoalY);
}

template<typename T>
T AStarSolve<T>::f(AStarPivot const& pivot) const {
	return pivot.g + h(pivot);
}

template<typename T>
int AStarSolve<T>::GetShortestPath(std::vector<std::vector<T>> inputMatrix, int startX, int startY, int goalX, int goalY) {
	this->StartX = startX;
	this->StartY = startY;
	this->GoalX = goalX;
	this->GoalY = goalY;
	this->Input = inputMatrix;
	this->Previous.clear();
	this->Previous.resize(inputMatrix.size());
	for(size_t i = 0; i < inputMatrix.size(); ++i) {
		this->Previous[i].resize(inputMatrix[i].size());
	}
	this->Pivots.clear();
	for(int i = 0; i < inputMatrix.size(); ++i) {
		std::vector<AStarPivot> temp;
		for(int j = 0; j < inputMatrix[0].size(); ++j) {
			temp.push_back(AStarPivot{j, i, INF});
		}
		this->Pivots.push_back(temp);
	}

	for(int i = 0; i < inputMatrix.size(); ++i) {
		for(int j = 0; j < inputMatrix[0].size(); ++j) {
			if(i > 0) {
				this->Pivots[i][j].neighbours.push_back(&this->Pivots[i - 1][j]);
			}
			if(j > 0) {
				this->Pivots[i][j].neighbours.push_back(&this->Pivots[i][j - 1]);
			}
			if(i < inputMatrix.size() - 1) {
				this->Pivots[i][j].neighbours.push_back(&this->Pivots[i + 1][j]);				
			}
			if(j < inputMatrix[0].size() - 1) {
				this->Pivots[i][j].neighbours.push_back(&this->Pivots[i][j + 1]);
			}
		}
	}

	this->Pivots[StartY][StartX].g = 0;

	Solve();

	return this->Pivots[GoalY][GoalX].g;
}

template<typename T>
bool AStarSolve<T>::Solve() {
	auto comparator = [this](AStarPivot const* l, AStarPivot const* r) {
		T const fl = f(*l);
		T const fr = f(*r);
		if(fl == fr) {
			return l < r;
		}
		return fl < fr;
	};
	std::set<AStarPivot*, decltype(comparator)> openSet(comparator);

	openSet.insert(&(this->Pivots[StartY][StartX]));

	do {
		auto ptrCurrent = openSet.begin(); // get min ptr
		auto const current = *ptrCurrent; // top()
		openSet.erase(ptrCurrent); // pop()

		if(current->x == GoalX && current->y == GoalY) {
			return true;
		}

		for(auto const neighbour : current->neighbours) {
			int const nextX = neighbour->x;
			int const nextY = neighbour->y;

			T score = current->g + Input[nextY][nextX];
			if(score < neighbour->g) {
				this->Previous[nextY][nextX] = { current->x, current->y };
				auto searchForNeighbour = openSet.find(neighbour);

				if(searchForNeighbour != openSet.end()) {
					// always remove, because the comparator value changes
					openSet.erase(neighbour);
				}

				neighbour->g = score;
				openSet.insert(neighbour);
			}
		}

	} while(!openSet.empty());

	return false;
}