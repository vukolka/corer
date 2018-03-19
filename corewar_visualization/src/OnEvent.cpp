
#include "CorewarVis.h"

void CorewarVis::OnEvent()
{
	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		if (events.type == SDL_QUIT)
			running = false;
		if (events.type == SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_c)
			{
				if (corewarUI.isRunning())
					corewarUI.changeState();
				gameBoard.processCycle(corewarUI.cycles);
				for (int i = corewarUI.cycles; i >= 0; --i)
				{
					if (gameBoard.processInput(corewarUI.cycles))
						endGame();
					corewarUI.getProcessesAmmount(gameBoard.processes.carrets.size());
					corewarUI.cycles--;
				}
			}
			if (events.key.keysym.sym == SDLK_ESCAPE)
				running = false;
			if (events.key.keysym.sym == SDLK_SPACE)
				corewarUI.changeState();
			if (events.key.keysym.sym == SDLK_RIGHT)
				if (!corewarUI.isRunning())
				{
					corewarUI.changeState();
					OnLoop();
					corewarUI.changeState();
				}
		}
	}
}

