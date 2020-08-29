#ifdef _CRT_SECURE_NO_WARNINGS
#undef _CRT_SECURE_NO_WARNINGS
#endif
#define _CRT_SECURE_NO_WARNINGS 1
#include "Game.h"

int main(int agrc, char* argv[])
{
	Game* game = NULL;
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart, frameDuration;

	game = new Game();
	game->init("Sliding Puzzle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);

	while (game->isRunning)
	{
		frameStart = SDL_GetTicks();

		game->handleEvent();
		game->update();
		game->render();

		frameDuration = SDL_GetTicks() - frameStart;
		if (frameDuration < frameDelay)
		{
			SDL_Delay(frameDelay - frameDuration);
		}
		else std::cout << "!!! FPS drop" << std::endl;
	}

	game->clean();

	return 0;
}