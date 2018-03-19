#include "Player.h"

Player::Player(std::string pName, std::string pDesc, int pid, int color)
{
	name = pName;
	descripion = pDesc;
	id = pid;
	curr_lives = 0;
	las_live = 0;
	switch (color)
	{
		case 3:
			playerColor = {0xff, 0, 0};
			break;
		case 1:
			playerColor = {0, 0xFF, 0};
			break;
		case 2:
			playerColor = {0, 0, 0xff};
			break;
		case 4:
			playerColor = {0, 0xFF, 0xFF};
			break;
		case 0:
			playerColor = {0xFF, 0xFF, 0xff};
			break;
		default:
			break;
	}
}

void Player::update(int cl, int ll)
{
	curr_lives = cl;
	las_live = ll;
}
