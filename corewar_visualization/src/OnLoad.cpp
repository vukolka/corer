#include <iostream>
#include <fcntl.h>
#include <fstream>
#include "CorewarVis.h"

using namespace std;

bool CorewarVis::OnLoad()
{
	mapFont = TTF_OpenFont("corewar_visualization/assets/ShareTechMono-Regular.ttf", 15);
	if( mapFont == NULL )
	{
		cout << "Can\'t get font, " << "SDL_Error :" << TTF_GetError() << endl;
		return (false);
	}

	textTexture.initTexture(renderer, mapFont);
	gamebg.initTexture(renderer, mapFont);
	gamebg.lHeight = screenHeight;
	gamebg.lWidth = screenWidth;
	gameBoard.initialParsing(renderer, mapFont);
	gameBoard.parceMap();
	corewarUI.initUI(&gameBoard.playersArray, &textTexture, screenHeight, screenWidth);
	killSound = Mix_LoadWAV("corewar_visualization/assets/Blaster-Ricochet.wav");
	if (!killSound)
		cout << "couldnt load kill sound, Mixer_Error: "<< Mix_GetError() << endl;
	endTrack = Mix_LoadMUS("corewar_visualization/assets/Imperial.wav");
	if (!endTrack)
		cout << "couldnt load star wars soundtrack, Mixer_Error: "<< Mix_GetError() << endl;
	return true;
}
