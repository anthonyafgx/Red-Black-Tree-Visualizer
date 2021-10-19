#pragma once
#include <string>
#include <vector>

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void insert(int key);
	class Node* GetRootNode() { return mRoot; }

	void AddNode(class Node* node);
	void RemoveNode(class Node* node);

private:
	class Node* mRoot;
	std::vector<class Node*> mNodes;
};

