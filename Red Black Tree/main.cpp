#include "GraphicsEngine.h"
#include <memory>

int main(int argc, char** argv)
{
	GraphicsEngine graphics;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// memory leak check

	bool success = graphics.Initialize();

	if (success)
	{
		graphics.GenerateOutput();
	}
	graphics.Shutdown();

	return 0;
}