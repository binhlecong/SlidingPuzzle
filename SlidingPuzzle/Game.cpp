#include "Game.h"
#include "TextureManager.h"
#include "TileManager.h"
#include "SlidingTile.h"
#include "UILabel.h"
#include <algorithm>

SDL_Renderer* Game::renderer;
SDL_Event Game::event;
bool Game::isRunning;

TileManager manager("Asset/Rhythmastic.png", 468, 468, 2, 2);

Game::Game()
{
	count = 0;
	window = NULL;
	renderer = NULL;
	isSolved = false;
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
		std::cout << "!!! Error : SDL" << std::endl;
		isRunning = false;
		isSolved = true;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "!!! Error : SDL_TTF" << std::endl;
		isRunning = false;
	}

	// add stuff
	manager.addTiles();
	manager.shuffleTiles();
}

void Game::handleEvent()
{
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
	{
		isRunning = false;
	}

	isSolved = manager.isSolved();
}

void Game::update()
{
	if (Game::event.type == SDL_KEYDOWN && !isSolved)
	{
		int direction = 0;
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_w:
			direction = UP;
			break;
			
		case SDLK_a:
			direction = LEFT;
			break;

		case SDLK_s:
			direction = DOWN;
			break;

		case SDLK_d:
			direction = RIGHT;
			break;

		case SDLK_ESCAPE:
			Game::isRunning = false;
			break;

		default:
			return;
		}

		manager.swapTiles(direction);
	}
}

void Game::render()
{
	SDL_RenderClear(Game::renderer);

	if(isSolved)
	{
		std::cout << "Solved" << std::endl;
		isRunning = false;
	}
	else
	{
		manager.drawTiles();
	}
	
	SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
	std::cout << "<<< Game cleared..." << std::endl;
}