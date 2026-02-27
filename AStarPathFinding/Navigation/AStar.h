#pragma once

#include <vector>
#include "Node.h"

template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

class AStar
{
	struct Direction
	{
		int x = 0, y = 0;
		float cost = 0.f;
	};

public:
	AStar();
	~AStar();

	std::vector<Node*> FindPath(
		Node* startNode, Node* goalNode,
		std::vector<std::vector<int>>& grid
	);

	void DisplayGridWithPath(
		std::vector<std::vector<int>>& grid,
		const std::vector<Node*>& path
	);

private:
	std::vector<Node*> ConstructPath(Node* goalNode);

	float CalculateHeuristic(Node* currentNode, Node* goalNode);

	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

	bool HasVisited(int x, int y, float gCost);

	bool IsDestination(const Node* const node);

	void DisplayGrid(std::vector<std::vector<int>>& grid);

private:
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
};

