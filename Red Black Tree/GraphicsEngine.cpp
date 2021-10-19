#include "GraphicsEngine.h"
#include "SDL_image.h"
#include "RedBlackTree.h"
#include "Node.h"

GraphicsEngine::GraphicsEngine() : 
	mIsRunning(true),
	mWindow(nullptr), 
	mRenderer(nullptr),
	mWindowWidth(1280),
	mWindowHeight(720)
{}

bool GraphicsEngine::Initialize()
{
	// create window
	mWindow = SDL_CreateWindow(
		"Red Black Tree Graphics - Anthony Ferrer y Javier Carrillo",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		mWindowWidth,
		mWindowHeight,
		0
	);

	if (!mWindow)
	{
		SDL_Log("Unable to create SDL_Window: %s", SDL_GetError());
		return false;
	};

	// create renderer
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Unable to create SDL_Renderer: %s", SDL_GetError());
		return false;
	}

	// Antialias
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

	// SDL Image
	int imgFlags = IMG_INIT_PNG;
	int imgInit = IMG_Init(imgFlags);

	if ((imgInit&imgFlags) != imgFlags)
	{
		SDL_Log("Unable to initialize IMAGE support: %s\n", IMG_GetError());
		system("pause");
		mIsRunning = false;
		return false;
	}

	LoadData();
	return true;
}

void GraphicsEngine::LoadData()
{
	// Instert RBTree functions
	RBTree.insert(8);
	RBTree.insert(14);
	RBTree.insert(1);
	RBTree.insert(3);
	RBTree.insert(6);
	RBTree.insert(4);
	RBTree.insert(7);
	RBTree.insert(13);
	RBTree.insert(10);

}

void GraphicsEngine::GenerateOutput()
{
	// Draw background
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 200, 255);
	SDL_RenderClear(mRenderer);

	// Draw every node
	RBTree.GetRootNode()->DrawNode(this, Coordinates(640, 50), 1.0f);

	SDL_RenderPresent(mRenderer);

	// Handle SDL Events (Windows buttons)
	while (mIsRunning)
	{
		UpdateWindow();
	}
}

void GraphicsEngine::UpdateWindow()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:				//< press close button
			mIsRunning = false;
			break;

		default:
			break;
		}
	}
}

void GraphicsEngine::Shutdown()
{
	for (auto texture : mTextures)
	{
		SDL_DestroyTexture(texture.second);
	}

	IMG_Quit();
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

SDL_Texture* GraphicsEngine::GetTexture(std::string path)
{
	// Pointer that will be returned
	SDL_Texture* tex = nullptr;

	// Check if file exists
	struct stat buffer;
	bool exists = (stat(path.c_str(), &buffer) == 0);

	if (!exists)
	{
		printf("ERROR: Could not find %s\n", path.c_str());
		// handle error
		system("pause");
		mIsRunning = false;
		return nullptr;
	}

	auto itr = mTextures.find(path);

	// if found, return pointer directly
	if (itr != mTextures.end())
	{
		return itr->second;
	}
	else
	{
		// Load path image to surface
		SDL_Surface* surface = IMG_Load(path.c_str());
		if (!surface)
		{
			// unable to load image
			SDL_Log("Unable to load image: %s\n", path.c_str(), IMG_GetError());
			// handle error
		}

		// Convert surface to texture
		tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (!tex)
		{
			SDL_Log("Unable to convert surface to texture '%s' due to: %s\n", path.c_str(), SDL_GetError());
			// handle error
			system("pause");
			mIsRunning = false;
		}

		// Delete Surface
		SDL_FreeSurface(surface);

		// Add tex to Map
		mTextures.emplace(path, tex);
	}

	// Return tex
	return tex;
}