#pragma once
#include <string>

class RedBlackTree
{
public:
	RedBlackTree();

	void insert(int key);
	class Node* GetRootNode() { return mRoot; }

private:
	class Node* mRoot;
};

