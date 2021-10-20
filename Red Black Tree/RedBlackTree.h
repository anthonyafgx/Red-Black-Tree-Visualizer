#pragma once
#include <string>
#include <vector>

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	// Data Structure Methods
	void Insert(int key);
	
	// Getters / Setters
	class Node* GetRootNode() { return mRoot; }
	void SetRoot(Node* node) { mRoot = node; }
	// Other methods
	void AddNode(class Node* node);		//< Add node to mNodes 
	void RemoveNode(class Node* node);	//< Remove nodes from mNodes
	
private:
	void FixInsertion(class Node* newNode);

private:
	class Node* mRoot;
	std::vector<class Node*> mNodes;
};

