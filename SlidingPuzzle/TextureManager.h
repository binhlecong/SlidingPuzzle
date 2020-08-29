#pragma once
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{
public:
	static SDL_Texture* loadTexture(const char* fileName);
	static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect desRect, SDL_RendererFlip flip);
};

