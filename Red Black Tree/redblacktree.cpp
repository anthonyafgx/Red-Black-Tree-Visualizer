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
	newNode->SetColor('r');

	// if there's no root
	if (!mRoot)
	{
		newNode->SetColor('b');
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
		if (newNode->GetParent()->GetColor() == 'r')
		{
			FixInsertion(newNode);
		}
	}
	
}

void RedBlackTree::FixInsertion(Node* newNode)
{
	if (!newNode->GetParent())	// if does not have parent
	{
		return;
	}

	if (newNode->GetParent()->GetColor() == 'b')	// if parent is black
	{
		return;
	}

	Node* u;

	while (newNode->GetParent()->GetColor() == 'r')
	{
		if (newNode->GetParent()->IsRight())	// Parent is Right
		{
			// Case 3.1: Uncle is Red.
			if (newNode->GetUncleColor() == 'r')
			{
				newNode->GetUncle()->SetColor('b');
				newNode->GetParent()->SetColor('b');
				newNode->GetGrandParent()->SetColor('r');
				newNode = newNode->GetGrandParent();
			}
			else
				// Case 3.2: Uncle is Black.
			{
				// Case 3.2.2: Parent is Right Child and NewNode is Left Child.
				if (newNode->IsLeft())
				{
					newNode = newNode->GetParent();
					newNode->RightRotation();
				}
				// Case 3.2.1: Parent is Right Child and NewNode is Right Child.
				newNode->GetParent()->SetColor('b');
				newNode->GetGrandParent()->SetColor('r');
				newNode->GetGrandParent()->LeftRotation();
			}
		}
		else if (newNode->GetParent()->IsLeft())	// Parent is Left
		{
			// Case 3.1: Uncle is Red.
			if (newNode->GetUncleColor() == 'r')
			{
				newNode->GetUncle()->SetColor('b');
				newNode->GetParent()->SetColor('b');
				newNode->GetGrandParent()->SetColor('r');
				newNode = newNode->GetGrandParent();
			}
			else
				// Case 3.2 (mirror): Uncle is Black or Null.
			{
				// Case 3.2.3: Parent is Left Child, NewNode is Right Child.
				if (newNode->IsRight())
				{
					newNode = newNode->GetParent();
					newNode->LeftRotation();
				}
				// Case 3.2.1 Parent is Left Child, NewNode is Left Child
				newNode->GetParent()->SetColor('b');
				newNode->GetGrandParent()->SetColor('r');
				newNode->GetGrandParent()->RightRotation();
			}

		}
		if (newNode == mRoot)
		{
			break;
		}
	}
	mRoot->SetColor('b');
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