#include "CorewarVis.h"
#include <iostream>

using namespace std;

bool CorewarVis::OnInit()
{
	bool success_flag = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Can\'t initialize SDL, " << "SDL_Error :" << SDL_GetError() << endl;
		return (false);
	}
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return (false);
	}
	if (TTF_Init() == -1)
	{
		cout << "Can\'t initialize TTF, " << "SDL_Error :" << TTF_GetError() << endl;
		return (false);
	}
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		cout << "Can\'t initialize IMG with PNG flag, " << "SDL_Error :" << IMG_GetError() << endl;
		return (false);
	}
	if ((window = SDL_CreateWindow("Corewar visualization",
						  SDL_WINDOWPOS_UNDEFINED,
						  SDL_WINDOWPOS_UNDEFINED,
						  screenWidth,
						  screenHeight,
						  SDL_WINDOW_SHOWN)) == nullptr)
	{
		cout << "Can\'t creat window, " << "SDL_Error :" << SDL_GetError() << endl;
		return (false);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (!renderer)
	{
		cout << "Can\'t creat renderer" << "SDL_Error :" << SDL_GetError() << endl;
		return (false);
	}
	if ((screenSurface = SDL_GetWindowSurface(window)) == nullptr)
	{
		cout << "Can\'t get window surface, " << "SDL_Error :" << SDL_GetError() << endl;
		return (false);
	}
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);
	return (true);
}


