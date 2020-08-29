#pragma once
#include "SlidingTile.h"
#include "TextureManager.h"
#include <vector>
#include <algorithm>

class SlidingTile;

#define UP    1
#define RIGHT 2
#define DOWN  3
#define LEFT  4

class TileManager
{
public:
	TileManager() = default;
	TileManager(const char* fileName, int imgSizeX, int imgSizeY, int widthNum, int heightNum);
	void addTiles();
	void swapTiles(int dir);
	void shuffleTiles();
	void drawTiles();
	~TileManager();
	
	int widthSize, heightSize;
	int imgSizeX, imgSizeY;
	const char* filePath;

	SlidingTile* emptyTile;
	std::vector<SlidingTile> tiles;
};