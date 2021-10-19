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
	Node(RedBlackTree* tree, int key);
	~Node();

	void DrawNode(class GraphicsEngine* graphics, const Coordinates pos, float scale);
	
	// Setters / Getters
	int GetKey() const { return mKey; }
	void SetKey(int key) { mKey = key; }
	Node* GetParent() const { return mParent; }
	void SetParent(Node* node) { mParent = node; }
	Node* GetLeft() const { return mLeft; }
	void SetLeft(Node* node) { mLeft = node; }
	Node* GetRight() const { return mRight; }
	void SetRight(Node* node) { mRight = node; }
	void SetColor(std::string str) { color = str; }

private:	
	int mKey;
	Node* mParent;
	Node* mLeft;
	Node* mRight;

private:
	std::string color;
	RedBlackTree* mTree;
};

