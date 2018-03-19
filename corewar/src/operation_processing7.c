/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_processing7.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:09:56 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:09:57 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void			process_operation(t_process *current_proc, t_environment *env)
{
	if (current_proc->command_cache->op_code <= 16 &&
		current_proc->command_cache->op_code > 0
		&& g_op_tab[current_proc->command_cache->op_code
				- 1].valid(current_proc, env))
	{
		current_proc->success = 1;
		debug_log(current_proc, env, 1);
		g_op_tab[current_proc->command_cache->op_code - 1].func(current_proc,
																env);
	}
	else
	{
		current_proc->success = 0;
		debug_log(current_proc, env, 0);
		just_skip(current_proc, env);
	}
}

void			just_skip(t_process *process, t_environment *env)
{
	process->success = 0;
	if (*process->program_counter == 0 || *process->program_counter > 16)
	{
		process->program_counter = get_adr(process->program_counter, 1, env);
		set_delay(process);
		return ;
	}
	if (env->debug_flag)
		print_movement(process, env, 0, count_swipe(process, env));
	process->program_counter = get_adr(process->program_counter,
									count_swipe(process, env), env);
	set_delay(process);
}

int				check_val_regs(t_process *process, t_environment *env)
{
	int		i;
	char	tmp;

	i = 0;
	(void)env;
	while (i < 3)
	{
		tmp = *process->command_cache->args[i];
		if (process->command_cache->codage[i] == 'R' &&
			(tmp <= 0 || tmp > 16))
			return (0);
		i++;
	}
	return (1);
}
