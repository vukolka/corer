#include <iostream>
#include <zconf.h>
#include <fcntl.h>
#include <assert.h>
#include "Map.h"
#include "TextureObj.h"
#include <stdio.h>

using namespace std;

void Map::putMap(TextureObj &texture)
{
	int k = 0;
	texture.loadTextureFromText(cols.c_str(), {150, 150, 150});
	texture.render(MAP_OFFSET_X + 8, MAP_OFFSET_Y - 20);

	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
	for (int i = 0; i < MAP_UNITS; ++i)
	{
		mapCache[i + MEM_SIZE]->render(5 + MAP_OFFSET_X - 20, i * 15 + MAP_OFFSET_Y);
		for (int j = 0; j < MAP_UNITS * 3; j += 3)
		{
			mapCache[k]->render((8 * (j + 1)) + MAP_OFFSET_X , i * 15 + MAP_OFFSET_Y);
			k++;
		}
	}
}

Map::Map()
{
	lastMove = nullptr;
	int	j;
	for (int i = 0; i < MAP_UNITS; ++i)
	{
		if (i < 10)
		{
			rows += "0";
			rows += to_string(i);
			cols += "0";
			cols += to_string(i);
		}
		else
		{
			cols += to_string(i);
			rows += to_string(i);
		}
		cols += " ";
		rows += "\n";
		for (j = 0; j < MAP_UNITS * 3; j += 3)
			strcpy(map[i] + j, "AA ");
		map[i][j] = 0;
	}
}

void Map::processProcesses()
{
	string	line;
	int		id;
	int		index;

	processes.kill_processes();
	while (getline(*inputFile, line))
	{
		if (line == "<processes>")
			continue;
		if (line == "</processes>")
			return ;
		id = stoi(line.substr(2, line.find(">")));
		line.erase(0, line.find(">") + 1);
		index = stoi(line.substr(2, line.find("]")));
		processes.create(id, index);
	}
}

void Map::updatePlayers()
{
	string	line;
	int		id;
	int		ll;
	int 	cl;

	while (true)
	{
		if (line == "</players>")
			break;
		getline(*inputFile, line);
		if (line == "</players>")
			break;
		id = stoi(line.substr(2, line.find(" ")));
		line.erase(0, line.find(" ") + 1);
		cl = stoi(line.substr(1, line.find(">")));
		line.erase(0, line.find(" ") + 1);
		ll = stoi(line.substr(1, line.find(">")));
		updatePlayer(id ,cl, ll);
	}
}

void	Map::transormToAscii(char *line, unsigned char sym)
{
	unsigned char a = sym / 16;
	unsigned char b = sym % 16;
	a = (a < 10) ? a + 48 : a + 87;
	b = (b < 10) ? b + 48 : b + 87;
	line[0] = a;
	line[1] = b;
	line[2] = 0;
}

int Map::initialParsing(SDL_Renderer *inRenderer, TTF_Font *inFont)
{
	inputFile = new ifstream("../log.txt");
	string	line;
	mapRenderer = inRenderer;
	mapFont = inFont;
	getline(*inputFile, line);

	if (line == "<players descr>")
		parcePlayersDesc();

	return 0;
}

void Map::parcePlayersDesc()
{
	int		id;
	string	line;
	string	name;
	string	desc;
	int		color = 1;

	while (getline(*inputFile, line))
	{
		if (line == "</players descr>")
			break;
		id = stoi(line.substr(2, line.find_first_of('>') - 1));
		line.erase(0, line.find(">") + 3);
		name = line.substr(0, line.find_first_of('>'));
		line.erase(0, line.find_first_of('<') + 1);
		if (line.find_first_of('>') == string::npos)
		{
			while (line.find_first_of(">") == string::npos)
				getline(*inputFile, line);
			desc = line;
		}
		else
			desc = line.substr(0, line.find_first_of('>'));
		playersArray.push_back(Player(name, desc, id, color));
		color++;
	}
}

void Map::renderProcesses(SDL_Renderer *renderer)
{
	processes.renderProcesses(renderer);
}

bool Map::parceMap()
{
	int fd = open("../map.txt", O_RDONLY);
	unsigned char data[4096];
	int players = playersArray.size() - 1;
	if (playersArray.size() == 0)
		exit(0);
	int	j;
	int k = 0;
	int switcher = 1;
	read(fd, &data, 4096);

	for (int i = 0; i < MAP_UNITS; ++i)
	{
		string pos = "";
		if (i < 10)
		{
			pos = "0";
		}
		pos += to_string(i);
		mapCache[i + MEM_SIZE] = new TextureObj();
		mapCache[i + MEM_SIZE]->initTexture(mapRenderer, mapFont);
		mapCache[i + MEM_SIZE]->loadTextureFromText(pos.c_str(), {150, 150, 150});
		for (j = 0; j < MAP_UNITS * 3; j += 3)
		{
			if (data[k] == data[k + 1] && data[k + 1] == data[k + 2]
					&& data[k + 2] == data[k + 3] && data[k] == 0 && data[k + 4] == 0)
				switcher = 0;
			if (switcher == 0 && data[k])
			{
				switcher = 1;
				players--;
			}
			if (switcher == 1)
				mapColors[k] = playersArray[players].id;
			else
				mapColors[k] = -1;
			transormToAscii((char *)map[i] + j, data[k]);
			mapCache[k] = new TextureObj();
			mapCache[k]->initTexture(mapRenderer, mapFont);
			if (mapColors[k] != -1)
			{
				mapCache[k]->loadTextureFromText(map[i] + j, getPlayerById(mapColors[k]));
				mapCache[k]->setInitialColor();
			}else
			{
				mapCache[k]->loadTextureFromText(map[i] + j, {0xFF, 0xFF, 0xFF});
			}
			k++;
		}
		map[i][j] = 0;
	}
	close(fd);
	return (true);
}

bool Map::processInput(int &aCycles)
{
	string line;

	for (int i = 0; i < 4; ++i)
	{
		getline(*inputFile, line);
		if (line.empty() || line == "end")
			return true;
		if (line == "<players>")
			updatePlayers();
		if (line == "<processes>")
		{
			processProcesses();
			aCycles++;
		}
		if (line == "<cycle>")
			i -= 2;
		if (line == "<events>")
			processEvents();

	}
	return (false);
}

void Map::updatePlayer(int id, int cl, int ll)
{
	for(auto &i : playersArray)
	{
		if (i.id == id)
		{
			i.curr_lives = cl;
			i.las_live = ll;
			break;
		}
	}
}

void Map::processEvents()
{
	//[<player_id> <change_start_index> <int_1> <int_2> ... <int_j>]
	string line;
	int args[20];
	int i = 0;
	while (getline(*inputFile, line))
	{
		if (line == "</events>")
			break;
		while (line.size() > 2)
		{
			args[i] = stoi(line.substr(2, line.find_first_of('>') - 1));
			line.erase(0, line.find_first_of('>') + 1);
			i++;
		}
		args[i] = 0;
		modifyMap(args, i);
		i = 0;
	}
}

void Map::modifyMap(int *pInt, int args_ammount)
{
	int x = (pInt[1] % MAP_UNITS) * 3;
	int y = pInt[1] / MAP_UNITS;
	int i = 2;
	int k = pInt[1];
	while (i < args_ammount)
	{
		if (x >= MAP_UNITS * 3)
		{
			x = 0;
			y++;
		}
		if (y >= MAP_UNITS)
		{
			y = 0;
			k = 0;
		}
		mapColors[k] = pInt[0];
		transormToAscii(map[y] + x, static_cast<unsigned char>(pInt[i]));
		mapCache[k]->loadTextureFromText(map[y] + x, getPlayerById(mapColors[k]));
		if (lastMove)
			lastMove->setInitialColor();
		lastMove = mapCache[k];
		k++;
		i++;
		x += 3;
	}
}

void Map::processCycle(int &cycles)
{
	string line;
	getline(cin, line);
	int cycle = stoi(line);
	inputFile->close();
	inputFile->open("../log.txt");
	while (getline(*inputFile, line))
	{
		if (line == "<cycle>")
		{
			getline(*inputFile, line);
			if (cycle == stoi(line.substr(2, line.find_first_of('>') - 1)))
				break;
		}
	}
	cycles = cycle + 1;
	for (auto i : mapCache)
		delete(i);
	lastMove = nullptr;
	inputFile->close();
	delete(inputFile);
	inputFile = new ifstream("../log.txt");
	parceMap();
}

SDL_Color & Map::getPlayerById(int id)
{
	for (auto &i : playersArray)
	{
		if (i.id == id)
			return i.playerColor;
	}
	auto csa = playersArray[0].playerColor;
	return (csa);
}

