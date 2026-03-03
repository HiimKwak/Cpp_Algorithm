#include "Partition/QuadTree.h"
#include <iostream>

class Level
{
public:
	Level() = default;
	~Level()
	{
		for (Node*& node : nodeList)
		{
			SafeDelete(node);
		}
		nodeList.clear();
	}

	void AddNewNode(Node* newNode)
	{
		nodeList.emplace_back(newNode); // 원랜 큐에 쌓아놓고 프레임 루프 이후에 처리해야함
	}

	inline const std::vector<Node*>& GetAllNodes() const { return nodeList; }

private:
	std::vector<Node*> nodeList;
};

int main()
{
	Level level;
	level.AddNewNode(new Node(Bounds(60, 80)));
	level.AddNewNode(new Node(Bounds(50, 80)));
	level.AddNewNode(new Node(Bounds(90, 120)));
	level.AddNewNode(new Node(Bounds(150, 150)));
	level.AddNewNode(new Node(Bounds(10, 10)));

	QuadTree tree(Bounds(0, 0, 200, 200));

	for (Node* node : level.GetAllNodes())
	{
		tree.Insert(node);
	}

	std::cout << "노드 삽입 완료\n";

	Node testNode(Bounds(45, 45, 20, 40));
	std::vector<Node*> intersects = tree.Query(&testNode);

	if (!intersects.empty())
	{
		std::cout << "겹치는 노드를 " << intersects.size() << "개 찾았습니다.\n";
	}
	else
	{
		std::cout << "겹치는 노드를 찾지 못했습니다.\n";
	}
}