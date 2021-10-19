#pragma once
#include <string>
#include "RedBlackTree.h"

struct Coordinates
{
	Coordinates(int x = 0, int y = 0) : x(x), y(y) {};
	int x;
	int y;
};

class Node
{	
public:
	// Constructor initializes everything to nullptr (except color).
	Node(RedBlackTree* tree, int key) {
		data = key;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		mTree = tree;

		mTree->AddNode(this);
	}

	~Node()
	{
		mTree->RemoveNode(this);
	}

	void DrawNode(class GraphicsEngine* graphics, const Coordinates pos, float scale);
	
	Node* GetParent() { return parent; }
	void SetColor(std::string str) { color = str; }

public:	
	int data;
	Node* parent;
	Node* left;
	Node* right;

private:
	std::string color;
	RedBlackTree* mTree;
};

