#pragma once
#include "TextureManager.h"
#include "TileManager.h"
#include <utility>

class SlidingTile
{
public:
	SlidingTile() = default;
	SlidingTile(SDL_Rect _srcRect, SDL_Rect _desRect, int xtrue, int ytrue, int id, const char* fileName);
	void drawTile();
	~SlidingTile();

	SDL_Texture* border;
	SDL_Rect tileRect;
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;
	std::pair<int, int> posTrue;
	int id;
};