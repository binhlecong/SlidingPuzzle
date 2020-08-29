#include "TileManager.h"

TileManager::TileManager(const char* fileName, int imgX, int imgY, int widthNum, int heightNum)
	:filePath(fileName), imgSizeX(imgX), imgSizeY(imgY), widthSize(widthNum), heightSize(heightNum)
{
}

TileManager::~TileManager()
{
	emptyTile->~SlidingTile();
	delete emptyTile;
	std::cout << "<<< Empty tile exture destroy" << std::endl;
}

void TileManager::addTiles()
{
	int tileHeight, tileWidth, id;
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
			id = y * heightSize + x;

			tiles.push_back(SlidingTile(src, des, x, y, id, filePath));
		}
	}

	tiles.back().srcRect = { 0,0,0,0 };

	// the last tile will have a different texture
	src.w = src.h = 20;
	src.x = src.y = 40;

	des.x = tileWidth * tileWidth;
	des.y = tileHeight * tileHeight;
	des.w = tileWidth;
	des.h = tileHeight;
	id = widthSize * heightSize - 1;

	emptyTile = new SlidingTile(src, des, widthSize - 1, heightSize -1, id, "Asset/arrows.png");
}

void TileManager::shuffleTiles()
{
	for (size_t i = 0; i < 50; i++)
	{
		int direction = rand() % 4 + 1;
		swapTiles(direction);
	}
}

void TileManager::swapTiles(int dir)
{
	int emptyX, emptyY;
	emptyX = emptyTile->posTrue.first;
	emptyY = emptyTile->posTrue.second;
	std::pair<int, int> selectedTile;

	switch (dir)
	{
	case UP:
		selectedTile.first = emptyX;
		selectedTile.second = emptyY + 1;
		selectedTile.second = std::min(selectedTile.second, heightSize - 1);
		emptyTile->posTrue.second = selectedTile.second;
		break;

	case LEFT:
		selectedTile.first = emptyX + 1;
		selectedTile.second = emptyY;
		selectedTile.first = std::min(selectedTile.first, widthSize - 1);
		emptyTile->posTrue.first = selectedTile.first;
		break;

	case DOWN:
		selectedTile.first = emptyX;
		selectedTile.second = emptyY - 1;
		selectedTile.second = std::max(selectedTile.second, 0);
		emptyTile->posTrue.second = selectedTile.second;
		break;

	case RIGHT:
		selectedTile.first = emptyX - 1;
		selectedTile.second = emptyY;
		selectedTile.first = std::max(selectedTile.first, 0);
		emptyTile->posTrue.first = selectedTile.first;
		break;

	default:
		break;
	}

	std::swap(tiles[selectedTile.second * widthSize
		+ selectedTile.first].srcRect,
		tiles[emptyY * widthSize
		+ emptyX].srcRect);

	emptyTile->desRect 
		= tiles[selectedTile.second * widthSize + selectedTile.first].desRect;

	if (emptyTile->posTrue.first == 0)
	{
		emptyTile->srcRect.x = 0;
	}
	else if (emptyTile->posTrue.first == widthSize - 1)
	{
		emptyTile->srcRect.x = 40;
	}
	else
	{
		emptyTile->srcRect.x = 20;
	}

	if (emptyTile->posTrue.second == 0)
	{
		emptyTile->srcRect.y = 0;
	}
	else if (emptyTile->posTrue.second == widthSize - 1)
	{
		emptyTile->srcRect.y = 40;
	}
	else
	{
		emptyTile->srcRect.y = 20;
	}
}

void TileManager::drawTiles()
{
	// draw normal tiles
	for (auto& t : tiles)
	{
		t.drawTile();
	}

	// draw arrows on the empty tile
	emptyTile->drawTile();
}