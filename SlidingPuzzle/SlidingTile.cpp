#include "SlidingTile.h"

SlidingTile::SlidingTile(SDL_Rect _srcRect, SDL_Rect _desRect, int xtrue, int ytrue, int id, const char* fileName)
{
	texture = TextureManager::loadTexture(fileName);
	border = TextureManager::loadTexture("Asset/border2.png");
	tileRect = { 0,0,200,200 };
	srcRect = _srcRect;
	desRect = _desRect;
	posTrue.first = xtrue;
	posTrue.second = ytrue;
	id = id;
}

SlidingTile::~SlidingTile()
{
	std::cout << "<<< Sprite texture destroyed! ..." << std::endl;
}

void SlidingTile::drawTile()
{
	TextureManager::draw(texture, srcRect, desRect, SDL_FLIP_NONE);
	TextureManager::draw(border, tileRect, desRect, SDL_FLIP_NONE);
}