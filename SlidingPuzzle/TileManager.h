#pragma once
#include "SlidingTile.h"
#include "TextureManager.h"
#include <vector>
#include <map>

class SlidingTile;

class TileManager
{
public:
	TileManager() = default;
	TileManager(const char* fileName, int imgSizeX, int imgSizeY, int widthNum, int heightNum);
	void addTiles();
	void drawTiles();
	~TileManager();
	std::pair<int, int> emptyTile;

	int widthSize, heightSize;
	int imgSizeX, imgSizeY;
	SDL_Texture* texture;
	const char* filePath;
	std::vector<SlidingTile> tiles;
	//std::map<int, SlidingTile> tiles;
};

