#include "CorewarVis.h"

void CorewarVis::OnRender()
{
	SDL_RenderClear(renderer);
	//gamebg.render(0, 0);
	gameBoard.renderProcesses(renderer);
	gameBoard.putMap(textTexture);
	corewarUI.renderUI();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
	SDL_RenderPresent(renderer);
}
