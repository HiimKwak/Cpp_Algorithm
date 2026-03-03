#include "Node.h"

Node::Node(const Bounds& bounds, int depth)
	: bounds(bounds), depth(depth)
{
}

Node::~Node()
{
	Clear();
}

void Node::Insert(Node* node)
{
	if (!node)
		return;

	NodeIndex result = TestRegion(node->GetBounds());

	if (result == NodeIndex::Straddling)
		points.emplace_back(node);
	else if (result != NodeIndex::OutOfArea)
	{
		if (Subdivide())
		{
			if (result == NodeIndex::TopLeft)
				topLeft->Insert(node);
			else if (result == NodeIndex::TopRight)
				topRight->Insert(node);
			else if (result == NodeIndex::BottomLeft)
				bottomLeft->Insert(node);
			else if (result == NodeIndex::BottomRight)
				bottomRight->Insert(node);
		}
		else
		{
			points.emplace_back(node);
		}
	}
}

void Node::Query(const Bounds& bounds, std::vector<Node*>& possibleNodes)
{
	possibleNodes.emplace_back(this);

	if (!IsDivided())
		return;

	std::vector<NodeIndex> quads = GetQuads(bounds);
	for (const NodeIndex& index : quads)
	{
		if (index == NodeIndex::TopLeft)
			topLeft->Query(bounds, possibleNodes);
		else if (index == NodeIndex::TopRight)
			topRight->Query(bounds, possibleNodes);
		else if (index == NodeIndex::BottomLeft)
			bottomLeft->Query(bounds, possibleNodes);
		else if (index == NodeIndex::BottomRight)
			bottomRight->Query(bounds, possibleNodes);
	}
}

void Node::Clear()
{
	points.clear(); // points에 추가되는 노드는 외부(level)에서 관리되는 노드이기 때문에 여기서 따로 해제해주지 않음
	if (IsDivided()) {
		topLeft->Clear();
		topRight->Clear();
		bottomLeft->Clear();
		bottomRight->Clear();

		ClearChildren();
	}
}

bool Node::Subdivide()
{
	if (depth == 5) // @incomplete: 최대깊이 임시 하드코딩
		return false;

	if (!IsDivided())
	{
		int x = bounds.X(), y = bounds.Y();
		int halfWidth = bounds.Width() / 2, halfHeight = bounds.Height() / 2;

		topLeft = new Node(Bounds(x, y, halfWidth, halfHeight), depth + 1);
		topRight = new Node(Bounds(x + halfWidth, y, halfWidth, halfHeight), depth + 1);
		bottomLeft = new Node(Bounds(x, y + halfHeight, halfWidth, halfHeight), depth + 1);
		bottomRight = new Node(Bounds(x + halfWidth, y + halfHeight, halfWidth, halfHeight), depth + 1);
	}

	return true;
}

bool Node::IsDivided()
{
	return topLeft != nullptr;
}

NodeIndex Node::TestRegion(const Bounds& bounds)
{
	std::vector<NodeIndex> quads = GetQuads(bounds);

	if (quads.empty())
		return NodeIndex::OutOfArea;

	if (quads.size() == 1)
		return quads[0];

	return NodeIndex::Straddling;
}

std::vector<NodeIndex> Node::GetQuads(const Bounds& bounds)
{
	std::vector<NodeIndex> quads;

	int x = this->bounds.X(), y = this->bounds.Y();
	int halfWidth = this->bounds.Width() / 2, halfHeight = this->bounds.Height() / 2;
	int centerX = x + halfWidth, centerY = y + halfHeight;

	bool left = bounds.X() < centerX && bounds.MaxX() >= x;
	bool right = bounds.MaxX() >= centerX && bounds.X() < this->bounds.MaxX();
	bool top = bounds.Y() < centerY && bounds.MaxX() >= y;
	bool bottom = bounds.MaxY() >= centerY && bounds.Y() < this->bounds.MaxY();

	if (top && left)
		quads.emplace_back(NodeIndex::TopLeft);
	if (top && right)
		quads.emplace_back(NodeIndex::TopRight);
	if (bottom && left)
		quads.emplace_back(NodeIndex::BottomLeft);
	if (bottom && right)
		quads.emplace_back(NodeIndex::BottomRight);

	return quads;
}

void Node::ClearChildren()
{
	if (IsDivided())
	{
		SafeDelete(topLeft);
		SafeDelete(topRight);
		SafeDelete(bottomLeft);
		SafeDelete(bottomRight);
	}
}
