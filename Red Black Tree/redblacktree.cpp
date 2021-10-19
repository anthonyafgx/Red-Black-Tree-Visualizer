#include "RedBlackTree.h"
#include "Node.h"

RedBlackTree::RedBlackTree() : mRoot(nullptr)
{

}

RedBlackTree::~RedBlackTree()
{
	while (!mNodes.empty())
	{
		delete mNodes.back();
	}
}

void RedBlackTree::Insert(int key)
{
	// TO DO: First validate if key alredy exists.

	Node* newNode = new Node(this, key);
	newNode->SetColor("red");

	// if there's no root
	if (!mRoot)
	{
		newNode->SetColor("black");
		mRoot = newNode;
		return;
	}


	/* BST Insertion */
	Node* y = nullptr;	//< x's parent
	Node* x = mRoot;

	// navigate down the tree
	while (x != nullptr)
	{
		y = x;
		if (newNode->GetKey() < x->GetKey())
		{
			x = x->GetLeft();
		}
		else if (newNode->GetKey() > x->GetKey())
		{
			x = x->GetRight();
		}
	}

	// insert node
	newNode->SetParent(y);
	if (newNode->GetKey() < y->GetKey())
	{
		y->SetLeft(newNode);
	}
	else if (newNode->GetKey() > y->GetKey())
	{
		y->SetRight(newNode);
	}
}

void RedBlackTree::AddNode(Node* node)
{
	mNodes.emplace_back(node);
}

void RedBlackTree::RemoveNode(Node* node)
{
	auto itr = std::find(mNodes.begin(), mNodes.end(), node);

	if (itr != mNodes.end())
	{
		mNodes.erase(itr);
	}
}

