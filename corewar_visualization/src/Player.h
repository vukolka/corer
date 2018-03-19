#ifndef COREWARVIS_PLAYER_H
#define COREWARVIS_PLAYER_H


#include <string>
#include <SDL_pixels.h>

class Player
{
public:
	Player(std::string pName, std::string pDesc, int id, int color);
	int			id;
	std::string name;
	std::string descripion;
	int			curr_lives;
	int			las_live;
	SDL_Color	playerColor;
	void		update(int cl, int ll);
};


#endif //COREWARVIS_PLAYER_H
