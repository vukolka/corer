#include "CorewarVis.h"

void CorewarVis::OnLoop()
{
	if (corewarUI.isRunning())
	{
		if (lasProcessAmmount > gameBoard.processes.carrets.size())
			Mix_PlayChannel(-1 ,killSound, 0);
		lasProcessAmmount = gameBoard.processes.carrets.size();
		if(gameBoard.processInput(corewarUI.cycles))
			endGame();
		corewarUI.getProcessesAmmount(gameBoard.processes.carrets.size());
	}
}

void CorewarVis::endGame()
{
	Player &winner = gameBoard.playersArray[0];
	for (auto &i : gameBoard.playersArray)
	{
		if (i.las_live < winner.las_live)
			winner = i;
	}
	SDL_RenderClear(renderer);
	textTexture.loadTextureFromText("GAME OVER", {0xFF, 0xFF, 0xFF});
	textTexture.render(screenWidth / 2 - 25, screenHeight / 2 - 20);



	std::string winner_string = "Winner is: ";
	winner_string += winner.name;
	textTexture.loadTextureFromText(winner_string.c_str(), {0xFF, 0xFF, 0xFF});
	textTexture.render(screenWidth / 2 - 50, screenHeight / 2 + 20);

	SDL_RenderPresent(renderer);
	Mix_PlayMusic(endTrack, 1000);
	SDL_Event events;
	while (1)
	{
		if (SDL_PollEvent(&events))
		{
			if (events.key.keysym.sym == SDLK_ESCAPE)
				exit(0);
			if (events.type == SDL_QUIT)
				exit(0);
		}
	}
}
