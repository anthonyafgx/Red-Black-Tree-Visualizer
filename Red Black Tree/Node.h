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

	void LeftRotation();
	void RightRotation();

	// Setters / Getters
	int GetKey() const { return mKey; }
	void SetKey(int key) { mKey = key; }
	Node* GetParent(){ return mParent; }
	void SetParent(Node* node) { mParent = node; }
	Node* GetLeft(){ return mLeft; }
	void SetLeft(Node* node) { mLeft = node; }
	Node* GetRight(){ return mRight; }
	void SetRight(Node* node) { mRight = node; }
	char GetColor() const { return mColor; }
	void SetColor(char c) { mColor = c; }

	// Special Getters
	Node* GetUncle();
	char GetUncleColor();
	Node* GetGrandParent();

	// Bools
	bool IsLeft();	// if node is left of parent
	bool IsRight();	// if node is right of parent
	bool IsRoot() { return !static_cast<bool>(mParent); }	// if node is root

	// Graphics
	void DrawNode(class GraphicsEngine* graphics, const Coordinates pos, float scale);

private:	
	int mKey;
	Node* mParent;
	Node* mLeft;
	Node* mRight;

private:
	char mColor;
	RedBlackTree* mTree;
};

