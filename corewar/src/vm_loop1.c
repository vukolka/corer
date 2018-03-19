/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_loop1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:15:10 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:15:11 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include "op.h"
#include "../libft/classes_lib/linked_list.h"
#include "../libft/classes_lib/queue.h"
#include "../libft/classes_lib/new.h"

void		last_hit_proc(t_environment *env, t_process *new_queue, int i)
{
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
		last_hit_proc(env, new_queue, i);
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
