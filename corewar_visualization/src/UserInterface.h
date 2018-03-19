#ifndef COREWARVIS_USERINTERFACE_H
#define COREWARVIS_USERINTERFACE_H


#include <vector>
#include "TextureObj.h"
#include "Player.h"

class UserInterface
{
private:
	std::vector<Player> *playersArray;
	bool	running;

	int 	processes_ammount;

	int		cycle_to_die;
	int 	cycle_delta;
	int 	nbr_live;
	int 	max_checks;

	int 	lWidth;
	int 	lHeight;

	TextureObj *UITexture;

public:
	int 	cycles;
	void 	getProcessesAmmount(int i);
	void 	incrementCycles();
	bool	isRunning();
	bool 	initUI(std::vector<Player> *p1, TextureObj *textTexture, int height, int width);
	void 	renderUI();
	void 	renderPlayer(Player &player, int &position);
	void	changeState();
	void 	updateUI(void *param);
	void 	renderInfo(int position);
};


#endif //COREWARVIS_USERINTERFACE_H
