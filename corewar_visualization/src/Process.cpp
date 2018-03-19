#include <SDL_rect.h>
#include <SDL_render.h>
#include <cstdlib>
#include <assert.h>
#include "Process.h"
#include "op.h"

void Process::renderProcesses(SDL_Renderer *renderer)
{
	int x;
	int y;
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xff, 0xff, 150);
	for (auto i : carrets)
	{
		y = i.index / MAP_UNITS * 15;
		x = i.index % MAP_UNITS * 24;
		SDL_Rect fillRect = {x + 7 + MAP_OFFSET_X, y + MAP_OFFSET_Y + 1, 18, 15};
		SDL_RenderFillRect( renderer, &fillRect);
	}
}

void Process::initProcesses()
{

}

void Process::update(int id, int index)
{
	t_process *current = find_by_id(id);
	assert(current);
	current->index = index;
}

void Process::updateProcesses()
{

}

bool Process::exists(int id)
{
	return (find_by_id(id) != nullptr);
}

void Process::create(int id, int index)
{
	carrets.push_back({id, index});
}

t_process *Process::find_by_id(int id)
{
	t_process *res;

	res = nullptr;
	for (auto &i : carrets)
	{
		if (i.p_id == id)
		{
			res = &i;
			break;
		}
	}
	return (res);
}

void Process::kill_processes()
{
	carrets.clear();
}

