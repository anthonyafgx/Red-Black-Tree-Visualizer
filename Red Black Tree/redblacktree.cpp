#include "RedBlackTree.h"
#include "Node.h"
#include <iostream>

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

	// Case 3: Parent is Red
	if (newNode->GetParent())	// has parent	
	{
		if (newNode->GetParent()->GetColor() == "red")
		{
			FixInsertion(newNode);
		}
	}
	
}

void RedBlackTree::FixInsertion(Node* newNode)
{
	// Case 3: Parent is Red.
	while (newNode->GetParent()->GetColor() == "red")
	{
		if (newNode->GetUncle())	// has uncle
		{
			// Case 3.1: Uncle is Red.
			if (newNode->GetUncle()->GetColor() == "red")
			{
				newNode->GetParent()->SetColor("black");
				newNode->GetUncle()->SetColor("black");
				if (!newNode->GetGrandParent()->IsRoot())	// if is not root
				{
					newNode->GetGrandParent()->SetColor("red");
				}
				break;
			}
		}
		// Case 3.2: Uncle is Black or Null
		else
		{
			if (newNode->GetParent()->IsRight())	// Parent is Right
			{
				// Case 3.2.1: Parent is right child, New Node is Right Child
				if (newNode->IsRight())
				{
					newNode->GetGrandParent()->LeftRotation();
					newNode->GetParent()->SetColor("black");
					// Recolor sibling
					if (newNode->IsRight())
					{
						newNode->GetParent()->GetLeft()->SetColor("red");
					}
					else if (newNode->IsLeft())
					{
						newNode->GetParent()->GetRight()->SetColor("black");
					}
				}
				// Case 3.2.2: Parent is right child, New Node is Left Child
				if (newNode->IsLeft())
				{
					newNode->GetParent()->RightRotation();
					// then 3.2.1 is applied
				}
			}
			else if (newNode->GetParent()->IsLeft())		// Parent is Left
			{
				// Case 3.2.3 (3.2.1 mirror): Parent is left child, New Node is Left Child
				if (newNode->IsLeft())
				{
					newNode->GetGrandParent()->RightRotation();
					newNode->GetParent()->SetColor("black");
					// Recolor sibling
					if (newNode->IsLeft())
					{
						newNode->GetParent()->GetRight()->SetColor("red");
					}
					else if (newNode->IsRight())
					{
						newNode->GetParent()->GetLeft()->SetColor("black");
					}
				}
				// Case 3.2.4 (3.2.4 mirror): Parent is left child, New Node is Right Child	
				else if (newNode->IsRight())
				{
					newNode->GetParent()->LeftRotation();
					// then 3.2.1 is applied
				}
			}
		}
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