#pragma once

class Position
{
public:
	int x = 0, y = 0;

	Position(int x, int y) : x(x), y(y) {}
};

class Node
{
public:
	Node(int x, int y, Node* parentNode = nullptr) : position(x, y), parentNode(parentNode) {}

	Position operator-(const Node& other) const
	{
		return Position(
			this->position.x - other.position.x,
			position.y - other.position.y
		);
	}

	bool operator==(const Node& other) const
	{
		return position.x == other.position.x &&
			position.y == other.position.y;
	}

public:
	Position position;
	float gCost = 0.f, hCost = 0.f, fCost = 0.f;
	Node* parentNode = nullptr;
};