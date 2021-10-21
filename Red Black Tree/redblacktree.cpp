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

void RedBlackTree::Delete(int key)
{
	Node* x = nullptr;
	Node* y = nullptr;
	Node* z = nullptr;
	
	Node* search = mRoot;

	// Search for key
	while (search != nullptr)
	{
		if (search->GetKey() == key)	// success
		{
			z = search;
		}

		if (search->GetKey() <= key)
		{
			search = search->GetRight();
		}
		else if (search->GetKey() > key)
		{
			search = search->GetLeft();
		}
	}

	if (!z)	// if not found (nullptr)
	{
		std::cout << "Key not found\n";
		return;
	}

	y = z;
	
	char yFirstColor = y->GetColor();

	if (!z->GetLeft() && !z->GetRight())	// if leaf node
	{
		// delete parent's childs
		z->GetParent()->SetRight(nullptr);
		z->GetParent()->SetLeft(nullptr);

		// delete node
		delete z;
		return;
	}
	else if (!z->GetLeft())			// if does not have left
	{
		x = z->GetRight();
		NodeReplace(z, z->GetRight());
	}
	else if (!z->GetRight())		// if does not have right
	{
		x = z->GetLeft();
		NodeReplace(z, z->GetLeft());
	}
	else
	{
		y = Minimum(z->GetRight());
		yFirstColor = y->GetColor();
		x = y->GetRight();
		if (y->GetParent() == z)
		{
			x->SetParent(y);
		}
		else
		{
			NodeReplace(y, y->GetRight());
			y->SetRight(z->GetRight());
			y->GetRight()->SetParent(y);
		}

		NodeReplace(z, y);
		y->GetLeft()->SetLeft(z->GetLeft());
		y->GetLeft()->SetParent(y);
		y->SetColor(z->GetColor());
	}
	delete z;

	if (yFirstColor == 'b')
	{
		FixDelete(x);
	}
}

void RedBlackTree::FixDelete(Node* node)
{
	Node* sibling;
	
	// Case 3: node is Black
	while (node->GetColor() == 'b' && node != mRoot)
	{
		if (node->IsLeft())
		{
			sibling = node->GetParent()->GetRight();	// Get Sibling
			
			// Case 3.1: Sibling is Red
			if (sibling->GetColor() == 'r')
			{
				sibling->SetColor('b');
				node->GetParent()->SetColor('r');
				node->GetParent()->LeftRotation();

				// update sibling variable
				sibling = node->GetParent()->GetRight();

				// now the case continues to case 3.2, 3.3 or 3.4 
			}

			// Case 3.2: Sibling is black and it's children are black
			if (sibling->GetLeft()->GetColor() == 'b' &&
				sibling->GetRight()->GetColor() == 'b')
			{
				sibling->SetColor('r');
				node->SetParent(node->GetParent());

				// now the case continues to 3.1
			}
			else
			{
				// Case 3.3: Sibling is black.
				//		Sibling's Left child is red.
				//		Sibling's Right child is black.
				if (sibling->GetLeft()->GetColor() == 'r' &&
					sibling->GetRight()->GetColor() == 'b')
				{
					sibling->GetLeft()->SetColor('b');
					sibling->SetColor('r');
					sibling->RightRotation();

					// update sibling variable
					sibling = node->GetParent()->GetRight();

					// continue to case 3.4 directly
				}
				// Case 3.4: Sibling is black.
				//		Sibling's Right child is red.
				sibling->GetRight()->SetColor('b');
				node->GetParent()->SetColor('b');
				node->GetParent()->LeftRotation();
				node = mRoot;
			}
		}
		else  // mirror previous cases. (interchange Left with Right).
		{
			sibling = node->GetParent()->GetLeft();	// Get Sibling

			// Case 3.1: Sibling is Red
			if (sibling->GetColor() == 'r')
			{
				sibling->SetColor('b');
				node->GetParent()->SetColor('r');
				node->GetParent()->RightRotation();

				// update sibling variable
				sibling = node->GetParent()->GetLeft();

				// now the case continues to case 3.2, 3.3 or 3.4 
			}

			// Case 3.2: Sibling is black and it's children are black
			if (sibling->GetRight()->GetColor() == 'b' &&
				sibling->GetLeft()->GetColor() == 'b')
			{
				sibling->SetColor('r');
				node->SetParent(node->GetParent());

				// now the case continues to 3.1
			}
			else
			{
				// Case 3.3: Sibling is black.
				//		Sibling's Right child is red.
				//		Sibling's Left child is black.
				if (sibling->GetRight()->GetColor() == 'r' &&
					sibling->GetLeft()->GetColor() == 'b')
				{
					sibling->GetRight()->SetColor('b');
					sibling->SetColor('r');
					sibling->LeftRotation();

					// update sibling variable
					sibling = node->GetParent()->GetLeft();

					// continue to case 3.4 directly
				}
				// Case 3.4: Sibling is black.
				//		Sibling's Left child is red.
				sibling->GetLeft()->SetColor('b');
				node->GetParent()->SetColor('b');
				node->GetParent()->RightRotation();
				node = mRoot;
			}
		}
	}
	node->SetColor('b');
}

Node* RedBlackTree::Find(int key)
{
	Node* search = mRoot;

	while (search)
	{
		if (key == search->GetKey())
		{
			break;
		}
		else
		{
			if (key > search->GetKey())
			{
				search = search->GetRight();
			}
			else
			{
				search = search->GetLeft();
			}
		}
	}

	return search;
}

void RedBlackTree::PreOrderTraversal(Node* node)
{
	// explore recursively down the tree.
	if (node)	// not null
	{
		std::cout << node->GetKey() << std::endl;
		PreOrderTraversal(node->GetLeft());
		PreOrderTraversal(node->GetRight());
	}
}

void RedBlackTree::InOrderTraversal(Node* node)
{
	// explore recursively down the tree.
	if (node)	// not null
	{
		InOrderTraversal(node->GetLeft());
		std::cout << node->GetKey() << std::endl;
		InOrderTraversal(node->GetRight());
	}
}

void RedBlackTree::PostOrderTraversal(Node* node)
{
	// explore recursively down the tree.
	if (node)	// not null
	{
		PostOrderTraversal(node->GetLeft());
		PostOrderTraversal(node->GetRight());
		std::cout << node->GetKey() << std::endl;
	}
}

Node* RedBlackTree::Minimum()
{
	return Minimum(mRoot);
}

Node* RedBlackTree::Minimum(Node* startNode)
{
	// path is all the way left.
	while (startNode->GetLeft())		// while not nullptr
	{
		startNode = startNode->GetLeft();
	}
	return startNode;
}

Node* RedBlackTree::Maximum()
{
	return Maximum(mRoot);
}

Node* RedBlackTree::Maximum(Node* startNode)
{
	// path is all the way right.
	while (startNode->GetLeft())		// while not nullptr
	{
		startNode = startNode->GetRight();
	}
	return startNode;
}

/* Node b will take the place of Node a */
void RedBlackTree::NodeReplace(Node* a, Node* b)
{
	if (!a->GetParent())
	{
		mRoot = b;
	}
	else if (a->IsLeft())
	{
		a->GetParent()->SetLeft(b);
	}
	else if (a->IsRight())
	{
		a->GetParent()->SetRight(b);
	}

	b->SetParent(a->GetParent());
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