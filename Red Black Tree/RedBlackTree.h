#pragma once
#include <string>
#include <vector>
#include <queue>

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	// Data Structure Methods
	void Insert(int key);
	void Delete(int key);
	class Node* Find(int key);
	void PreOrderTraversal(Node* node);
	void InOrderTraversal(Node* node);
	void PostOrderTraversal(Node* node);
	class Node* Minimum();
	class Node* Minimum(class Node* startNode);	// overload
	class Node* Maximum();
	class Node* Maximum(class Node* startNode);	// overload
	
	

	// Getters / Setters
	class Node* GetRootNode() { return mRoot; }
	void SetRoot(Node* node) { mRoot = node; }
	// Other methods
	void AddNode(class Node* node);		//< Add node to mNodes 
	void RemoveNode(class Node* node);	//< Remove nodes from mNodes
	
private:
	// Internal Data Structure Methods
	void FixInsertion(class Node* newNode);
	void FixDelete(class Node* node);

	// Replace
	void NodeReplace(Node* a, Node* b);

private:
	class Node* mRoot;
	std::vector<class Node*> mNodes;
};

