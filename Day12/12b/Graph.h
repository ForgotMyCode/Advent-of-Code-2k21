#pragma once

#include <unordered_set>
#include <vector>

class Graph {
public:
	void AddEdge(size_t from, bool fromIsSmall, size_t to, bool toIsSmall);

	size_t FindPaths(size_t const start, size_t const end) const;

private:
	void AddConnectionToNode(size_t from, bool isSmall, size_t to);

	class TraversalPivot {
	public:
		TraversalPivot(size_t node);

		inline
		bool HasVisited(size_t query) const {
			return Visited.find(query) != Visited.end();
		}

		inline
		void Visit(size_t query) {
			Visited.insert(query);
			Node = query;
		}

		inline
		size_t GetNode() const {
			return Node;
		}

		inline
		bool UsedVisitTwice() {
			return bUsedVisitTwice;
		}

		inline
		void UseVisitTwice() {
			bUsedVisitTwice = true;
		}

	private:
		std::unordered_set<size_t> Visited;
		size_t Node;
		bool bUsedVisitTwice = false;
	};


	inline
	bool CanVisit(TraversalPivot const& pivot, size_t node) const {
		return !(Nodes[node].IsSmall() && pivot.HasVisited(node));
	}

	class Node {
	public:
		Node(bool isSmall);

		inline
		void ConnectWith(size_t other) {
			To.push_back(other);
		}

		inline
		bool IsSmall() const {
			return bIsSmall;
		}

		inline
		std::vector<size_t> const& GetNext() const {
			return To;
		}

	private:
		std::vector<size_t> To;
		bool bIsSmall;
	};


	std::vector<Node> Nodes;
};