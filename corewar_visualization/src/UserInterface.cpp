//
// Created by vukolov on 19.02.18.
//

#include <memory.h>
#include "UserInterface.h"
#include "op.h"
#include "TextureObj.h"

bool UserInterface::initUI(std::vector<Player> *players, TextureObj *textTexture, int height, int width)
{
	running = false;

	cycles = processes_ammount = 0;
	playersArray = players;
	cycle_delta = CYCLE_DELTA;
	cycle_to_die = CYCLE_TO_DIE;
	max_checks = MAX_CHECKS;
	nbr_live = NBR_LIVE;

	cycles = -1;
	lWidth = width;
	lHeight = height;
	UITexture = textTexture;
	return false;
}

void UserInterface::renderUI()
{
	int xScale = lWidth / 5 * 4;

	std::string processes = "Processes ";
	processes += std::to_string(processes_ammount);
	int position = 200;
	if (running)
		UITexture->loadTextureFromText("Running", {0xff, 0xff, 0xff});
	else
		UITexture->loadTextureFromText("Paused", {0xff, 0xff, 0xff});
	UITexture->render(xScale, 40);
	UITexture->loadTextureFromText(const_cast<char *>(processes.c_str()), {0xff, 0xff, 0xff});
	UITexture->render(xScale, 80);

	for (int j = static_cast<int>(playersArray->size() - 1); j >= 0; --j)
	{
		renderPlayer(playersArray->at(j), position);
		position += 20;
	}
//	for(auto &i : *playersArray)
//	{
//		renderPlayer(i, position);
//		position += 20;
//	}
	renderInfo(position);
	std::string currentUIElem;

	currentUIElem = "Cycles: ";
	if (cycles == -1)
		currentUIElem += std::to_string(0);
	else
		currentUIElem += std::to_string(cycles);
	UITexture->loadTextureFromText(const_cast<char *>(currentUIElem.c_str()), {0xff, 0xff, 0xff});
	UITexture->render(xScale, 120);
}

void UserInterface::changeState()
{
	running = !running;
}

bool UserInterface::isRunning()
{
	return running;
}

void UserInterface::renderPlayer(Player &player, int &position)
{
	int xScale = lWidth / 5 * 4;
	std::string currentUIElem;

	currentUIElem = "Player ";
	currentUIElem += std::to_string(player.id) += ": ";
	currentUIElem += player.name;
	UITexture->loadTextureFromText(const_cast<char *>(currentUIElem.c_str()), {0xff, 0xff, 0xff});
	UITexture->render(xScale, position + 40);
	currentUIElem = "Last live: ";
	currentUIElem += std::to_string(player.las_live);
	UITexture->loadTextureFromText(const_cast<char *>(currentUIElem.c_str()), {0xff, 0xff, 0xff});
	UITexture->render(xScale, position + 60);
	currentUIElem = "Lives in current period: ";
	currentUIElem += std::to_string(player.curr_lives);
	UITexture->loadTextureFromText(const_cast<char *>(currentUIElem.c_str()), {0xff, 0xff, 0xff});
	UITexture->render(xScale, position + 80);
	position += 80;
}

void UserInterface::renderInfo(int position)
{
	int xScale = lWidth / 5 * 4;
	std::string currentUIElem;

	position += 40;
	currentUIElem = "CYCLES_TO_DIE: ";
	currentUIElem += std::to_string(cycle_to_die);
	UITexture->loadTextureFromText(const_cast<char *>(currentUIElem.c_str()), {0xff, 0xff, 0xff});
	UITexture->render(xScale, position + 40);
	currentUIElem = "CYCLES_DELTA: ";
	currentUIElem += std::to_string(cycle_delta);
	UITexture->loadTextureFromText(const_cast<char *>(currentUIElem.c_str()), {0xff, 0xff, 0xff});
	UITexture->render(xScale, position + 80);
	currentUIElem = "NMBR_LIVE: ";
	currentUIElem += std::to_string(nbr_live);
	UITexture->loadTextureFromText(const_cast<char *>(currentUIElem.c_str()), {0xff, 0xff, 0xff});
	UITexture->render(xScale, position + 120);
	currentUIElem = "Max_checks: ";
	currentUIElem += std::to_string(max_checks);
	UITexture->loadTextureFromText(const_cast<char *>(currentUIElem.c_str()), {0xff, 0xff, 0xff});
	UITexture->render(xScale, position + 160);
}

void UserInterface::incrementCycles()
{
	cycles++;
}

void UserInterface::getProcessesAmmount(int i)
{
	processes_ammount = i;
}
