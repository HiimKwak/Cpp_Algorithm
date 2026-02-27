#include <iostream>
#include <vector>
#include <Windows.h>

#include "Navigation/Node.h"
#include "Navigation/AStar.h"

std::vector<std::vector<int>> grid =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 1 },
	{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

void FindStartAndGoalNode(std::vector<std::vector<int>>& grid, Node*& outStartNode, Node*& outGoalNode);

int main()
{
	CONSOLE_CURSOR_INFO info = {};
	info.dwSize = 1;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	Node* startNode = nullptr;
	Node* goalNode = nullptr;
	FindStartAndGoalNode(grid, startNode, goalNode);

	if (!startNode || !goalNode)
	{
		SafeDelete(startNode);
		SafeDelete(goalNode);

		return 0;
	}

	AStar aStar;
	auto path = aStar.FindPath(startNode, goalNode, grid);
	if (!path.empty())
	{
		std::cout << "\n경로 탐색 성공.\n";
		aStar.DisplayGridWithPath(grid, path);
	}
	else
	{
		std::cout << "\n경로 탐색 실패.\n";
	}

	SafeDelete(goalNode); // startNode와 달리 goalNode는 메모리 정리가 되지 않음

	COORD coord = { 0, 15 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cin.get();
}

void FindStartAndGoalNode(std::vector<std::vector<int>>& grid, Node*& outStartNode, Node*& outGoalNode)
{
	if (grid.empty() || grid[0].empty())
		return;

	for (int y = 0; y < static_cast<int>(grid.size()); ++y)
	{
		if (outStartNode && outGoalNode)
			break;

		for (int x = 0; x < static_cast<int>(grid[0].size()); ++x)
		{
			if (outStartNode && outGoalNode)
				break;

			if (grid[y][x] == 2)
			{
				outStartNode = new Node(x, y);
				continue;
			}
			if (grid[y][x] == 3)
			{
				outGoalNode = new Node(x, y);
				continue;
			}
		}
	}
}
