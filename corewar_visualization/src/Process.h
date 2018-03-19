//
// Created by vukolov on 19.02.18.
//

#ifndef COREWARVIS_PROCESS_H
#define COREWARVIS_PROCESS_H


#include <forward_list>
#include <vector>

typedef struct	s_process
{
	int			p_id;
	int 		index;
}				t_process;

class Process
{
private:
public:
	std::vector<t_process> carrets;
	void 		initProcesses();
	void		renderProcesses(SDL_Renderer *renderer);
	bool		exists(int id);
	void		create(int id, int index);
	void		update(int id, int index);
	void 		kill_processes();
	t_process * find_by_id(int id);

	void updateProcesses();
};


#endif //COREWARVIS_PROCESS_H
