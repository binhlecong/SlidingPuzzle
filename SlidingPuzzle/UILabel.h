#pragma once

#include "Game.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel
{
public:
	UILabel() = default;

	void setText (const char* text, int x, int y, int fontSize, SDL_Color color) 
	{
		TTF_Font* font = TTF_OpenFont("Asset/MilkyNice.ttf", fontSize);
		SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text, color, 700);

		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);

		position.x = x;
		position.y = y;
		position.w = surface->w;
		position.h = surface->h;

		SDL_FreeSurface(surface);
	}

	~UILabel()
	{
		SDL_DestroyTexture(labelTexture);
		std::cout << "<<< Text texture destroyed!..." << std::endl;
	}

	void draw()
	{
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

private:
	SDL_Rect position;
	SDL_Texture* labelTexture;
};