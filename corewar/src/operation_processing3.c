/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_processing3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:06:26 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:06:27 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include <libft.h>
#include <ft_printf/ft_printf.h>
#include "op.h"
#include "../libft/classes_lib/linked_list.h"
#include "../libft/classes_lib/queue.h"

void			ft_ld(t_process *process, t_environment *env)
{
	int	counter_swipe;

	counter_swipe = count_swipe(process, env);
	if (process->command_cache->codage[0] == 'D')
		n_cpy_reg(process, return_arg(process, env, 0),
				return_arg(process, env, 1), 4);
	else if (process->command_cache->codage[0] == 'I')
		n_cpy_reg(process,
				deconvert_arg(conv_mem(return_arg(process, env, 0))
								% IDX_MOD), return_arg(process, env, 1), 4);
	process->carry = conv_mem(return_arg(process, env, 1)) ? 0 : 1;
	process->program_counter =
			get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

void			ft_lld(t_process *process, t_environment *env)
{
	int	counter_swipe;

	counter_swipe = count_swipe(process, env);
	if (process->command_cache->codage[0] == 'D')
		n_cpy_reg(process, return_arg(process, env, 0),
				return_arg(process, env, 1), 4);
	else if (process->command_cache->codage[0] == 'I')
		n_cpy_reg(process, return_arg(process, env, 0),
				return_arg(process, env, 1), 4);
	process->carry = conv_mem(return_arg(process, env, 1)) ? 0 : 1;
	process->program_counter =
			get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

int				valid_st(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (process->command_cache->codage[0] == 'R' &&
		(process->command_cache->codage[1] == 'I'
		|| process->command_cache->codage[1] == 'R')
		&& check_val_regs(process, env))
		return (1);
	return (0);
}

void			ft_st(t_process *process, t_environment *env)
{
	int	counter_swipe;

	counter_swipe = count_swipe(process, env);
	if (process->command_cache->codage[1] == 'I')
	{
		n_cpy_map(env, return_arg(process, env, 0),
				return_ind(get_adr(process->program_counter,
									conv_mem(return_arg(process, env, 1))
									% IDX_MOD, env), env), 4);
		log_event(process, get_adr(process->program_counter,
								conv_mem(return_arg(process, env, 1))
								% IDX_MOD, env), env, 4);
	}
	else if (process->command_cache->codage[1] == 'R')
		n_cpy_reg(process, return_arg(process, env, 0),
				return_arg(process, env, 1), 4);
	process->program_counter =
			get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

int				valid_and(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (!ft_strchr(process->command_cache->codage, 'N')
		&& process->command_cache->codage[2] == 'R'
		&& check_val_regs(process, env))
		return (1);
	return (0);
}
