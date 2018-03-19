#include <ft_printf.h>
#include "op.h"
#include "../libft/classes_lib/linked_list.h"
#include "../libft/classes_lib/queue.h"
#include "../libft/classes_lib/new.h"

int		set_zero(t_environment *env)
{
	t_llist *t;

	t = (t_llist *)env->players;
	while (t)
	{
		((t_player *)t->content)->current_lives = 0;
		t = t->next;
	}
}

void		get_winner(t_environment *env)
{
	t_player	*winner;
	t_llist		*players;

	players = (t_llist *)env->players;
	winner = ((t_player *)players->content);
	while (players)
	{
		if (winner->last_live_cycle <
				((t_player *)players->content)->last_live_cycle)
			winner = ((t_player *)players->content);
		players = players->next;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n",
		winner->id,
		winner->name);
}

void		end_game(t_environment *env, int end)
{
	close(env->fd);
	close(env->debug_fd);
	if (end)
		get_winner(env);
	exit(0);
}

void		delete_proc(t_process **proc)
{
	(*proc)->program_counter = NULL;
	if ((*proc)->command_cache->codage)
		free((*proc)->command_cache->codage);
	free((*proc)->command_cache->args[2]);
	free((*proc)->command_cache->args[1]);
	free((*proc)->command_cache->args[0]);
	free((*proc)->command_cache->args);
	free((*proc)->command_cache);
	free(*proc);
}

void		kill_proc(t_environment *env)
{
	t_process	*new_queue;
	int			i;
	t_process	*proc;

	i = 0;
	if (env->cycles >= env->nextkill)
	{
		new_queue = NULL;
		set_zero(env);
		while (env->processes_queue)
		{
			proc = get_from_head(&env->processes_queue);
			if (proc->live_executions)
			{
				i += proc->live_executions;
				proc->live_executions = 0;
				add_to_tail(proc, &new_queue);
			}
			else
				delete_proc(&proc);
		}
		if (!new_queue)
			end_game(env, 1);
		free(env->processes_queue);
		env->processes_queue = new_queue;
		if (env->cyclestodie > CYCLE_DELTA)
		{
			if (i >= NBR_LIVE || env->last_check >= MAX_CHECKS)
			{
				env->cyclestodie = env->cyclestodie - CYCLE_DELTA;
				env->last_check = 0;
			}
			else
				env->last_check++;
		}
		else
			env->cyclestodie = 0;
		env->nextkill += env->cyclestodie;
	}
}

void		vm_loop(t_environment *environment)
{
	int running;

	running = 1;
	while (running)
	{
		if (environment->debug_flag)
			ft_printf_fd("It is now cycle %d\n",
				environment->debug_fd, environment->cycles + 1);
		make_turn(environment);
		kill_proc(environment);
		if (environment->vis_flag)
			log_state(environment);
		if (environment->cycles == environment->dump)
			dump_memory(environment);
	}
}
