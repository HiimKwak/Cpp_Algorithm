#include "AStar.h"

#include <Windows.h>
#include <algorithm>
#include <cmath>
#include <iostream>

AStar::AStar()
{
}

AStar::~AStar()
{
	for (Node* node : openList)
		SafeDelete(node);
	openList.clear();
	for (Node* node : closedList)
		SafeDelete(node);
	closedList.clear();
}

std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, std::vector<std::vector<int>>& grid)
{
	this->startNode = startNode;
	this->goalNode = goalNode;

	if (!this->startNode || !this->goalNode || grid.empty() || grid[0].empty())
		return std::vector<Node*>(); // return { }; 해도 컴파일러가 알아서 반환 타입으로 변환해줌

	openList.emplace_back(this->startNode);

	const float diagonalCost = 1.41421356f;
	std::vector<Direction> directions =
	{
		{ 0, 1, 1.0f }, { 0, -1, 1.0f}, {1, 0, 1.0f}, {-1, 0, 1.0f},
		{1,1, diagonalCost},{1,-1, diagonalCost},{-1,1, diagonalCost},{-1,-1, diagonalCost},
	};

	while (!openList.empty())
	{
		Node* lowestNode = openList[0];
		for (Node* const node : openList)
		{
			if (node->fCost < lowestNode->fCost)
				lowestNode = node;
		}

		Node* currentNode = lowestNode;
		if (IsDestination(currentNode))
			return ConstructPath(currentNode);

		for (auto iterator = openList.begin(); iterator != openList.end(); ++iterator)
		{
			if ((*iterator) == currentNode)
			{
				openList.erase(iterator);
				break;
			}
		}

		closedList.emplace_back(currentNode);

		for (const Direction& direction : directions)
		{
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;
			if (!IsInRange(newX, newY, grid))
				continue;
			if (grid[newY][newX] == 1)
				continue;

			float newGCost = currentNode->gCost + direction.cost;
			if (HasVisited(newX, newY, newGCost))
				continue;

			Node* neighborNode = new Node(newX, newY, currentNode);
			neighborNode->gCost = newGCost;
			neighborNode->hCost = CalculateHeuristic(neighborNode, this->goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			Node* openListNode = nullptr;
			for (Node* const node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			if (openListNode)
			{
				if (neighborNode->gCost < openListNode->gCost || neighborNode->fCost < openListNode->fCost)
				{
					openListNode->parentNode = neighborNode->parentNode;
					openListNode->gCost = neighborNode->gCost;
					openListNode->hCost = neighborNode->hCost;
					openListNode->fCost = neighborNode->fCost;
				}
				SafeDelete(neighborNode);
				continue;
			}

			if (grid[newY][newX] == 0)
				grid[newY][newX] = 5;

			openList.emplace_back(neighborNode);

			DisplayGrid(grid);
			DWORD delay = static_cast<DWORD>(0.05f * 1000);
			Sleep(delay);
		}
	}
	return {};
}

void AStar::DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
	static COORD position = { 0, 0 };
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, position);

	static int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	static int green = FOREGROUND_GREEN;
	static int red = FOREGROUND_RED;

	for (int y = 0; y < static_cast<int>(grid.size()); ++y)
	{
		for (int x = 0; x < static_cast<int>(grid[0].size()); ++x)
		{
			int& value = grid[y][x];
			if (value == 5)
				value = 0;
		}
	}

	for (int y = 0; y < static_cast<int>(grid.size()); ++y)
	{
		for (int x = 0; x < static_cast<int>(grid[0].size()); ++x)
		{
			int& value = grid[y][x];
			if (value == 2)
			{
				SetConsoleTextAttribute(handle, red);
				std::cout << "S ";
				continue;
			}
			if (value == 3)
			{
				SetConsoleTextAttribute(handle, red);
				std::cout << "G ";
				continue;
			}
			if (value == 1)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "# ";
				continue;
			}
			if (value == 0)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "0 ";
				continue;
			}
		}
		std::cout << "\n";
	}
	for (Node* const node : path)
	{
		COORD position{
			static_cast<short>(node->position.x * 2),
			static_cast<short>(node->position.y)
		};

		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, green);

		std::cout << "* ";
		DWORD delay = static_cast<DWORD>(0.05f * 1000);
		Sleep(delay);
	}
	position.X = 0;
	position.Y = 0;
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	std::vector<Node*> path;

	Node* currentNode = goalNode;
	while (currentNode)
	{
		path.emplace_back(currentNode);
		currentNode = (*currentNode).parentNode;
	}
	std::reverse(path.begin(), path.end());

	return path;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* goalNode)
{
	Position diff = *currentNode - *goalNode;
	return static_cast<float>(std::sqrt(diff.x * diff.x + diff.y * diff.y)); // 직선거리(빗변)를 휴리스틱 비용으로 산정
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
	if (grid.empty() || grid[0].empty())
		return false;

	if (x < 0 || x >= static_cast<int>(grid[0].size()) || y < 0 || y >= static_cast<int>(grid.size()))
		return false;

	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	for (Node* const node : openList)
	{
		if (node->position.x == x && node->position.y == y && gCost >= node->gCost)
			return true;
	}

	for (Node* const node : closedList)
	{
		if (node->position.x == x && node->position.y == y)
			return true;
	}

	return false;
}

bool AStar::IsDestination(const Node* const node)
{
	return *node == *goalNode;
}

void AStar::DisplayGrid(std::vector<std::vector<int>>& grid)
{
	static COORD position = { 0,0 };
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, position);

	static int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	static int green = FOREGROUND_GREEN;
	static int red = FOREGROUND_RED;

	for (int y = 0; y < static_cast<int>(grid.size()); ++y)
	{
		for (int x = 0; x < static_cast<int>(grid[0].size()); ++x)
		{
			if (grid[y][x] == 1)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "# ";
				continue;
			}

			if (grid[y][x] == 2)
			{
				SetConsoleTextAttribute(handle, red);
				std::cout << "S ";
				continue;
			}

			if (grid[y][x] == 3)
			{
				SetConsoleTextAttribute(handle, red);
				std::cout << "G ";
				continue;
			}

			if (grid[y][x] == 5)
			{
				SetConsoleTextAttribute(handle, green);
				std::cout << "+ ";
				continue;
			}

			if (grid[y][x] == 0)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "0 ";
			}
		}
		std::cout << "\n";
	}
	position.X = 0;
	position.Y = 0;
}
