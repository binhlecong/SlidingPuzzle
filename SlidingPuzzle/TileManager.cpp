#include "TileManager.h"

TileManager::TileManager(const char* fileName, int imgX, int imgY, int widthNum, int heightNum)
	:filePath(fileName), imgSizeX(imgX), imgSizeY(imgY), widthSize(widthNum), heightSize(heightNum)
{
	texture = TextureManager::loadTexture(fileName);
	emptyTile = std::make_pair(widthNum - 1, heightNum - 1);
}

TileManager::~TileManager()
{
	SDL_DestroyTexture(texture);
	std::cout << "<<< Texture destroy" << std::endl;
}

void TileManager::addTiles()
{
	int tileHeight, tileWidth;
	tileHeight = 800 / heightSize;
	tileWidth = 800 / widthSize;
	SDL_Rect src = { 0 }, des = { 0 };

	for (size_t y = 0; y < heightSize; y++)
	{
		for (size_t x = 0; x < widthSize; x++)
		{
			src.w = imgSizeX / widthSize;
			src.h = imgSizeY / heightSize;
			src.x = src.w * x;
			src.y = src.h * y;

			des.x = tileWidth * x;
			des.y = tileHeight * y;
			des.w = tileWidth;
			des.h = tileHeight;
			int id = y * heightSize + x;
			SlidingTile aTile(src, des, x, y, id, filePath);
			tiles.push_back(aTile);
		}
	}

	// remove the last to make an empty tile
	tiles.back().srcRect = { 0,0,0,0 };
}

void TileManager::drawTiles()
{
	for (auto& t : tiles)
	{
		t.drawTile();
	}
}