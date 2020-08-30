#include "TileManager.h"

TileManager::TileManager(const char* fileName, int imgX, int imgY, int widthNum, int heightNum)
	:filePath(fileName), imgSizeX(imgX), imgSizeY(imgY), widthSize(widthNum), heightSize(heightNum)
{
	emptyTile = NULL;
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
			id = y * widthSize + x;

			tiles.push_back(SlidingTile(src, des, x, y, id, filePath));
		}
	}

	tiles.back().srcRect = { 0,0,0,0 };

	// the last tile will have a different texture
	src.w = src.h = 20;
	src.x = src.y = 40;

	des.x = tileWidth * (widthSize - 1);
	des.y = tileHeight * (heightSize - 1);
	des.w = tileWidth;
	des.h = tileHeight;
	id = widthSize * heightSize - 1;

	emptyTile = new SlidingTile(src, des, widthSize - 1, heightSize -1, id, "Asset/arrows.png");
}

void TileManager::shuffleTiles()
{
	srand(time(NULL));
	for (size_t i = 0; i < 100; i++)
	{
		int direction = rand() % 4 + 1;
		swapTiles(direction);
	}
}

void TileManager::swapTiles(int dir)
{
	int emptyX, emptyY;
	emptyX = emptyTile->curPos.first;
	emptyY = emptyTile->curPos.second;

	int selectedX, selectedY;
	selectedX = selectedY = 0;

	switch (dir)
	{
	case UP:
		selectedX = emptyX;
		selectedY = emptyY + 1;
		selectedY = std::min(selectedY, heightSize - 1);
		break;

	case LEFT:
		selectedX = emptyX + 1;
		selectedY = emptyY;
		selectedX = std::min(selectedX, widthSize - 1);
		break;

	case DOWN:
		selectedX = emptyX;
		selectedY = emptyY - 1;
		selectedY = std::max(selectedY, 0);
		break;

	case RIGHT:
		selectedX = emptyX - 1;
		selectedY = emptyY;
		selectedX = std::max(selectedX, 0);
		break;

	default:
		break;
	}

	std::swap(tiles[selectedY * widthSize
		+ selectedX].srcRect,
		tiles[emptyY * widthSize
		+ emptyX].srcRect);

	std::swap(tiles[selectedY * widthSize
		+ selectedX].curPos,
		tiles[emptyY * widthSize
		+ emptyX].curPos);

	emptyTile->desRect 
		= tiles[selectedY * widthSize + selectedX].desRect;
	emptyTile->curPos
		= tiles[selectedY * widthSize + selectedX].truePos;

	if (emptyTile->curPos.first == 0)
	{
		emptyTile->srcRect.x = 0;
	}
	else if (emptyTile->curPos.first == widthSize - 1)
	{
		emptyTile->srcRect.x = 40;
	}
	else
	{
		emptyTile->srcRect.x = 20;
	}

	if (emptyTile->curPos.second == 0)
	{
		emptyTile->srcRect.y = 0;
	}
	else if (emptyTile->curPos.second == heightSize - 1)
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

bool TileManager::isSolved()
{
	for  (auto& t : tiles)
	{
		if (t.curPos != t.truePos)
		{
			return false;
		}
	}
	return true;
}