#include "Graph.h"

#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;


void Graph::AddEdge(size_t from, bool fromIsSmall, size_t to, bool toIsSmall) {
	if(from > to) {
		AddEdge(to, toIsSmall, from, fromIsSmall);
		return;
	}

	AddConnectionToNode(from, fromIsSmall, to);
	AddConnectionToNode(to, toIsSmall, from);
}

size_t Graph::FindPaths(size_t const start, size_t const end) const {
	stack<TraversalPivot> s;

	s.push(TraversalPivot(start));

	size_t pathsFound = 0;

	do {
		TraversalPivot pivot = s.top();
		s.pop();

		if(pivot.GetNode() == end) {
			++pathsFound;
			continue;
		}

		vector<size_t> const& next = Nodes[pivot.GetNode()].GetNext();

		for(size_t query : next) {
			if(query != start) {
				if(!CanVisit(pivot, query)) {
					if(pivot.UsedVisitTwice()) {
						continue;
					}

					TraversalPivot nextPivot(pivot);
					nextPivot.Visit(query);
					nextPivot.UseVisitTwice();

					s.push(nextPivot);
				}
				else {
					TraversalPivot nextPivot(pivot);
					nextPivot.Visit(query);

					s.push(nextPivot);
				}
			}
		}

	} while(!s.empty());

	return pathsFound;
}

void Graph::AddConnectionToNode(size_t from, bool isSmall, size_t to) {
	if(from > Nodes.size()) {
		throw exception("trying to insert uninitialized node!");
	}
	if(from == Nodes.size()) {
		Nodes.push_back(Node{ isSmall });
	}
	Nodes[from].ConnectWith(to);
}


Graph::TraversalPivot::TraversalPivot(size_t node) : Node(node) {}


Graph::Node::Node(bool isSmall) : bIsSmall{ isSmall } {

}

