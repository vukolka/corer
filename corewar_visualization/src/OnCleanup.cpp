#include "CorewarVis.h"

void CorewarVis::OnCleanup()
{
	delete(gameBoard.inputFile);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_FreeChunk(killSound);
	SDL_Quit();
}
