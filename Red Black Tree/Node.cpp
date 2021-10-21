#include "Node.h"
#include "GraphicsEngine.h"
#include <string>
#include <iostream>

Node::Node(RedBlackTree* tree, int key) :
	mKey(key),
	mTree(tree),
	mParent(nullptr),
	mLeft(nullptr),
	mRight(nullptr)
{
	mTree->AddNode(this);
}

Node::~Node()
{
	mTree->RemoveNode(this);
}

void Node::LeftRotation()
{
	Node* y = mRight;

	if (y)	// if y is not nullptr
	{
		mRight = y->GetLeft();

		if (y->GetLeft())	// if exists
		{
			y->GetLeft()->SetParent(this);
		}

		y->SetParent(mParent);

		if (!mParent)	// if root
		{
			mTree->SetRoot(y);
		}
		else if (this == mParent->GetLeft())
		{
			mParent->SetLeft(y);
		}
		else if (this == mParent->GetRight())
		{
			mParent->SetRight(y);
		}

		y->SetLeft(this);
		mParent = y;
	}
	else
	{
		std::cout << "INFO: Could not perform LeftRotation\n";
		return;
	}
}

void Node::RightRotation()
{
	Node* y = mLeft;

	if (y)	// if y is not nullptr
	{
		mLeft = y->GetRight();

		if (y->GetRight())	// if exists
		{
			y->GetRight()->SetParent(this);
		}

		y->SetParent(mParent);

		if (!mParent)	// if root
		{
			mTree->SetRoot(y);
		}
		else if (this == mParent->GetLeft())
		{
			mParent->SetLeft(y);
		}
		else if (this == mParent->GetRight())
		{
			mParent->SetRight(y);
		}

		y->SetRight(this);
		mParent = y;
	}
	else
	{
		std::cout << "INFO: Could not perform RightRotation\n";
		return;
	}
}

void Node::DrawNode(GraphicsEngine* graphics, const Coordinates pos, float scale)
{
	// Tuning Variables

	/* distance multiplier between nodes
	* where n = balls of distance (in x and y direction)
	*/
	const float NODES_DISTANCE = 1.5f;

	/* offset distance multiplier between root node and child nodes */
	float ROOT_OFFSET_DISTANCE = 3.0f;

	int texWidth;
	int texHeight;

	std::string pathColor;
	if (mColor == 'r')
	{
		pathColor = "redcircle";
	}
	else if (mColor == 'b')
	{
		pathColor = "blackcircle";
	}
	else
	{
		SDL_Log("Error, no color found in Node");
	}

	std::string path = "Assets/" + pathColor + "/" + std::to_string(mKey) + ".png";

	SDL_Texture* texture = graphics->GetTexture(path);
	SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);

	/* DRAW LINES */
	// positions of childs
	if (mParent != nullptr)
	{
		ROOT_OFFSET_DISTANCE = 1;
	}

	Coordinates leftPos = Coordinates(pos.x - texWidth * scale * NODES_DISTANCE * ROOT_OFFSET_DISTANCE,
		pos.y + texHeight * scale * NODES_DISTANCE);

	Coordinates rightPos = Coordinates(pos.x + texWidth * scale * NODES_DISTANCE * ROOT_OFFSET_DISTANCE,
		pos.y + texHeight * scale * NODES_DISTANCE);

	SDL_SetRenderDrawColor(graphics->GetRenderer(), 10, 10, 10, 255);

	if (mLeft)
	{
		SDL_RenderDrawLine(
			graphics->GetRenderer(),
			pos.x,
			pos.y,
			leftPos.x,
			leftPos.y
			);
	}
	if (mRight)
	{
		SDL_RenderDrawLine(
			graphics->GetRenderer(),
			pos.x,
			pos.y,
			rightPos.x,
			rightPos.y
		);
	}


	/* DRAW CIRCLES */
	if (texture)
	{
		SDL_Rect r;

		// Resize to scale
		r.w = static_cast<int>(texWidth * scale);
		r.h = static_cast<int>(texHeight * scale);

		// Set position
		r.x = static_cast<int>(pos.x - r.w / 2);	//< Formula to get top-left corner.
		r.y = static_cast<int>(pos.y - r.h / 2);

		SDL_RenderCopy(
			graphics->GetRenderer(),
			texture,
			nullptr,
			&r
		);
	}

	// Draw Childs
	if (mLeft)
	{
		mLeft->DrawNode(graphics, leftPos, scale);
	}
	if (mRight)
	{
		mRight->DrawNode(graphics, rightPos, scale);
	}
}

Node* Node::GetUncle()
{
	if (mParent)					// has parent
	{
		if (mParent->GetParent())	// has grandparent
		{
			if (mParent->IsLeft())
			{
				return mParent->GetParent()->GetRight();
			}
			else if (mParent->IsRight())
			{
				return mParent->GetParent()->GetLeft();
			}
			else
			{
				std::cout << "INFO: Uncle not found\n";
				return nullptr;
			}
		}
		else
		{
			std::cout << "Node does not have grand parent\n";
			return nullptr;
		}
	}
	else
	{
		std::cout << "INFO: Node does not have parent\n";
		return nullptr;
	}
}

char Node::GetUncleColor()
{
	if (!GetUncle())	// if uncle is nullptr
	{
		return 'b';
	}
	else
	{
		return GetUncle()->GetColor();
	}
}

Node* Node::GetGrandParent()
{
	if (GetParent())
	{
		return mParent->GetParent();
	}
}

bool Node::IsRight()
{
	if (mParent->GetRight())
	{
		return this == mParent->GetRight();
	}
}

bool Node::IsLeft()
{
	if (mParent->GetLeft())
	{
		return this == mParent->GetLeft();
	}
}