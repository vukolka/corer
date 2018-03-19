/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_processing5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:07:43 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:07:44 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int				fork_valid(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	return (1);
}

void			malloc_cache(t_process *new)
{
	new->command_cache =
			(t_command_cache *)ft_memalloc(sizeof(t_command_cache));
	new->command_cache->args =
			(unsigned char **)ft_memalloc(sizeof(unsigned char *) * 3);
	new->command_cache->args[0] =
			(unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
	new->command_cache->args[1] =
			(unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
	new->command_cache->args[2] =
			(unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
}

void			ft_fork(t_process *process, t_environment *env)
{
	t_process	*new;
	int			tmp;

	new = (t_process *)ft_memalloc(sizeof(t_process));
	new->player_id = process->player_id;
	new->carry = process->carry;
	new->live_executions = process->live_executions;
	n_cpy_reg(new, &(process->memory[0]), &(new->memory[0]), 64);
	tmp = convert_arg(return_arg(process, env, 0), process, 0);
	new->program_counter = get_adr(process->program_counter,
								tmp % IDX_MOD, env);
	malloc_cache(new);
	new->id = ++env->count_proc;
	process->program_counter = get_adr(process->program_counter, 3, env);
	new->new = 1;
	set_delay(process);
	set_delay(new);
	add_to_head(new, &env->processes_queue);
}

void			ft_zjmp(t_process *process, t_environment *env)
{
	int tmp;

	if (process->carry)
	{
		tmp = convert_arg(return_arg(process, env, 0), process, 0);
		process->program_counter =
				get_adr(process->program_counter, tmp % IDX_MOD, env);
		process->success = 1;
	}
	else
	{
		process->program_counter = get_adr(process->program_counter, 3, env);
		process->success = 0;
	}
	set_delay(process);
}

void			ft_lfork(t_process *process, t_environment *env)
{
	t_process	*new;
	int			tmp;

	new = (t_process *)ft_memalloc(sizeof(t_process));
	new->player_id = process->player_id;
	new->carry = process->carry;
	new->live_executions = process->live_executions;
	n_cpy_reg(new, &(process->memory[0]), &(new->memory[0]), 64);
	tmp = convert_arg(return_arg(process, env, 0), process, 0);
	new->program_counter = get_adr(process->program_counter, tmp, env);
	malloc_cache(new);
	new->id = ++env->count_proc;
	process->program_counter = get_adr(process->program_counter, 3, env);
	process->success = 1;
	new->new = 1;
	set_delay(process);
	set_delay(new);
	add_to_head(new, &env->processes_queue);
}
