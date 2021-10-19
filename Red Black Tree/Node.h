#pragma once
#include <string>

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
	Node(int key) {
		data = key;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	void DrawNode(class GraphicsEngine* graphics, const Coordinates pos, float scale);
	
	Node* GetParent() { return parent; }
	void SetColor(std::string str) { color = str; }

public:
	int data;
	std::string color;
	Node* parent;
	Node* left;
	Node* right;

private:

};

