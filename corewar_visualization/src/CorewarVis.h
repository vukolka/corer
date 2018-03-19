#ifndef COREWARVIS_COREWARVIS_H
#define COREWARVIS_COREWARVIS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Map.h"
#include "TextureObj.h"
#include "UserInterface.h"
#include "Process.h"
#include "Player.h"
#include <forward_list>
#include "SDL_mixer.h"
class CorewarVis
{
private:
	SDL_Window		*window;
	SDL_Surface		*screenSurface;
	SDL_Renderer	*renderer;
	TTF_Font		*mapFont;
	TextureObj		textTexture;
	TextureObj		gamebg;
	Map				gameBoard;
	UserInterface	corewarUI;
	Process			processes;
	Mix_Chunk		*killSound;
	Mix_Music		*endTrack;
	unsigned int 	lasProcessAmmount;

	int 			screenWidth;
	int 			screenHeight;

	bool			running;

	bool 			OnInit();
	bool 			OnLoad();
	void			OnEvent();
	void 			OnLoop();
	void			OnRender();
	void			OnCleanup();
public:
	int				OnExecute();
	CorewarVis(int width, int height);

	void endGame();
};


#endif
