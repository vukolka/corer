#ifndef COREWARVIS_MAP_H
#define COREWARVIS_MAP_H

#include <SDL_render.h>
#include "TextureObj.h"
#include "op.h"
#include "Process.h"
#include "Player.h"
#include <fstream>
class Map
{
private:
	char 	map[MAP_UNITS][MAP_UNITS * 3 + 1];
public:
	std::ifstream				*inputFile;
	Process			 			processes;
	std::vector<Player>			playersArray;
	int							mapColors[MEM_SIZE];
	TextureObj					*mapCache[MEM_SIZE + MAP_UNITS];
	TextureObj					*lastMove;
	SDL_Renderer				*mapRenderer;
	TTF_Font					*mapFont;
	std::string					rows;
	std::string					cols;
	int 						lastProcessesCycles;

	Map();

	void					putMap(TextureObj &texture);
	bool					parceMap();
	void 					processProcesses();
	void 					transormToAscii(char *line, unsigned char sym);
	int 					initialParsing(SDL_Renderer *inRenderer, TTF_Font *inFont);
	void 					parcePlayersDesc();

	SDL_Color & getPlayerById(int id);

	void updatePlayers();

	void renderProcesses(SDL_Renderer *renderer);

	bool processInput(int &aCycles);

	void updatePlayer(int id, int cl, int ll);

	void processEvents();

	void modifyMap(int *pInt, int args_ammount);

	void processCycle(int &cycle);

	void endGame();

	int findPlayeId(int i);
};

#endif
