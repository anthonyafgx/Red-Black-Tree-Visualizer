#include "Node.h"
#include "GraphicsEngine.h"
#include <string>

// Tuning Variables

/* distance multiplier between nodes
* where n = balls of distance (in x and y direction)
*/
const float NODES_DISTANCE = 1.5f; 

/* offset distance multiplier between root node and child nodes */
float ROOT_OFFSET_DISTANCE = 3.0f;

void Node::DrawNode(GraphicsEngine* graphics, const Coordinates pos, float scale)
{
	int texWidth;
	int texHeight;

	std::string pathColor;
	if (color == "red")
	{
		pathColor = "redcircle";
	}
	else if (color == "black")
	{
		pathColor = "blackcircle";
	}
	else
	{
		SDL_Log("Error, no color found in Node");
	}

	std::string path = "Assets/" + pathColor + "/" + std::to_string(data) + ".png";

	SDL_Texture* texture = graphics->GetTexture(path);
	SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);

	/* DRAW LINES */
	// positions of childs
	if (parent != nullptr)
	{
		ROOT_OFFSET_DISTANCE = 1;
	}

	Coordinates leftPos = Coordinates(pos.x - texWidth * scale * NODES_DISTANCE * ROOT_OFFSET_DISTANCE,
		pos.y + texHeight * scale * NODES_DISTANCE);

	Coordinates rightPos = Coordinates(pos.x + texWidth * scale * NODES_DISTANCE * ROOT_OFFSET_DISTANCE,
		pos.y + texHeight * scale * NODES_DISTANCE);

	SDL_SetRenderDrawColor(graphics->GetRenderer(), 10, 10, 10, 255);

	if (left)
	{
		SDL_RenderDrawLine(
			graphics->GetRenderer(),
			pos.x,
			pos.y,
			leftPos.x,
			leftPos.y
			);
	}
	if (right)
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
	if (left)
	{
		left->DrawNode(graphics, leftPos, scale);
	}
	if (right)
	{
		right->DrawNode(graphics, rightPos, scale);
	}
}
