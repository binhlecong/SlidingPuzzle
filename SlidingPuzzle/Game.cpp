#include "Game.h"
#include "TextureManager.h"
#include "TileManager.h"
#include "SlidingTile.h"
#include <algorithm>

SDL_Renderer* Game::renderer;
SDL_Event Game::event;
bool Game::isRunning;

//SDL_Texture* background;
TileManager manager("Asset/background.png", 800, 800, 7, 7);

Game::Game()
{
	count = 0;
	window = NULL;
	renderer = NULL;
}

Game::~Game() {}

void Game::init(const char* title, int x, int y, int width, int height, bool fullScreen)
{
	int flag = 0;
	if (fullScreen)
	{
		flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << ">>> Subsystem initilised! ..." << std::endl;

		window = SDL_CreateWindow(title, x, y, width, height, flag);
		if (window)
		{
			std::cout << ">>> Window created! ..." << std::endl;
		}

		Game::renderer = SDL_CreateRenderer(window, -1, 0);
		if (Game::renderer)
		{
			SDL_SetRenderDrawColor(Game::renderer, 120, 120, 120, 255);
			std::cout << ">>> Renderer created! ..." << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	// add stuff
	manager.addTiles();
}

void Game::handleEvent()
{
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
	{
		isRunning = false;
	}
}

void Game::update()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		int emptyX, emptyY;
		emptyX = manager.emptyTile.first;
		emptyY = manager.emptyTile.second;
		std::pair<int, int> selectedTile;

		switch (Game::event.key.keysym.sym)
		{
		case SDLK_w:
			selectedTile.first = emptyX;
			selectedTile.second = emptyY + 1;
			selectedTile.second = std::min(selectedTile.second, manager.heightSize - 1);
			manager.emptyTile.second = selectedTile.second;
			break;
			
		case SDLK_a:
			selectedTile.first = emptyX + 1;
			selectedTile.second = emptyY;
			selectedTile.first = std::min(selectedTile.first, manager.widthSize - 1);
			manager.emptyTile.first = selectedTile.first;
			break;

		case SDLK_s:
			selectedTile.first = emptyX;
			selectedTile.second = emptyY - 1;
			selectedTile.second = std::max(selectedTile.second, 0);
			manager.emptyTile.second = selectedTile.second;
			break;

		case SDLK_d:
			selectedTile.first = emptyX - 1;
			selectedTile.second = emptyY;
			selectedTile.first = std::max(selectedTile.first, 0);
			manager.emptyTile.first = selectedTile.first;
			break;

		case SDLK_ESCAPE:
			Game::isRunning = false;
			break;

		default:
			return;
		}

		
		std::swap(manager.tiles[selectedTile.second * manager.widthSize 
			+ selectedTile.first].srcRect, 
			manager.tiles[emptyY * manager.widthSize 
			+ emptyX].srcRect);
	}
}

void Game::render()
{
	SDL_RenderClear(Game::renderer);
	/*SDL_Rect src = { 0, 0, 800, 800 }, des = { 0, 0, 800, 800 };
	TextureManager::draw(background, src, des, SDL_FLIP_NONE);*/
	manager.drawTiles();
	SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "<<< Game cleared..." << std::endl;
}