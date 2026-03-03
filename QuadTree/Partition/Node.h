#pragma once

#include "Bounds.h"
#include <vector>

template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

enum class NodeIndex
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	Straddling, // straddle: 걸쳐앉다, 양다리
	OutOfArea
};

class Node
{
public:
	Node(const Bounds& bounds, int depth = 0);
	~Node();

	void Insert(Node* node);
	void Query(const Bounds& bounds, std::vector<Node*>& possibleNodes);
	void Clear();

	inline const Bounds& GetBounds() const { return bounds; }
	inline const std::vector<Node*>& Points() const { return points; }
	inline Node* TopLeft() const { return topLeft; }
	inline Node* TopRight() const { return topRight; }
	inline Node* BottomLeft() const { return bottomLeft; }
	inline Node* BottomRight() const { return bottomRight; }

private:
	bool Subdivide();
	bool IsDivided();
	NodeIndex TestRegion(const Bounds& bounds);
	std::vector<NodeIndex> GetQuads(const Bounds& bounds);
	void ClearChildren();

private:
	int depth = 0;
	Bounds bounds;
	std::vector<Node*> points; // 현재 영역에 포함된 노드 목록
	Node* topLeft = nullptr;
	Node* topRight = nullptr;
	Node* bottomLeft = nullptr;
	Node* bottomRight = nullptr;
};

