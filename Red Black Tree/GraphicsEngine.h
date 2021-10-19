#pragma once
#include "SDL.h"
#include <unordered_map>
#include "RedBlackTree.h"

class GraphicsEngine
{
public: 
	GraphicsEngine();

	bool Initialize();
	void GenerateOutput();
	void Shutdown();

	SDL_Texture* GetTexture(std::string path);
	SDL_Renderer* GetRenderer() { return mRenderer; }

private:
	void UpdateWindow();
	void LoadData();
	
private:
	// tree
	class RedBlackTree RBTree;

	// info
	bool mIsRunning;

	// textures
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// SDL
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	const int mWindowWidth;
	const int mWindowHeight;
};

