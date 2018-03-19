/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_processing6.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:09:16 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:09:17 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int				ldi_valid(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (!ft_strchr(process->command_cache->codage, 'N')
		&& process->command_cache->codage[2] == 'R'
		&& process->command_cache->codage[1] != 'I'
		&& check_val_regs(process, env))
		return (1);
	return (0);
}

void			ft_ldi(t_process *process, t_environment *env)
{
	int	counter_swipe;
	int tmp;
	int tmp2;

	counter_swipe = count_swipe(process, env);
	tmp = (process->command_cache->codage[0] == 'R') ?
		conv_mem(return_arg(process, env, 0)) :
		convert_arg(return_arg(process, env, 0), process, 0);
	tmp = (process->command_cache->codage[0] == 'I') ?
		conv_mem(return_arg(process, env, 0)) : tmp;
	tmp2 = (process->command_cache->codage[1] == 'R') ?
		conv_mem(return_arg(process, env, 1)) :
		convert_arg(return_arg(process, env, 1), process, 1);
	n_cpy_reg(process, get_adr(process->program_counter,
	((tmp + tmp2) % IDX_MOD), env), return_arg(process, env, 2), 4);
	process->program_counter = get_adr(process->program_counter,
									counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

void			ft_lldi(t_process *process, t_environment *env)
{
	int	counter_swipe;
	int tmp;
	int tmp2;

	counter_swipe = count_swipe(process, env);
	tmp = (process->command_cache->codage[0] == 'R') ?
		conv_mem(return_arg(process, env, 0)) :
		convert_arg(return_arg(process, env, 0), process, 0);
	tmp = (process->command_cache->codage[0] == 'I') ?
		conv_mem(return_arg(process, env, 0)) : tmp;
	tmp2 = (process->command_cache->codage[1] == 'R') ?
		conv_mem(return_arg(process, env, 1)) :
		convert_arg(return_arg(process, env, 1), process, 1);
	n_cpy_reg(process, get_adr(process->program_counter,
							(tmp + tmp2), env), return_arg(process, env, 2), 4);
	process->carry = conv_mem(return_arg(process, env, 2)) ? 0 : 1;
	process->program_counter = get_adr(process->program_counter,
									counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

int				sti_valid(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (!ft_strchr(process->command_cache->codage, 'N')
		&& process->command_cache->codage[0] == 'R'
		&& process->command_cache->codage[2] != 'I'
		&& check_val_regs(process, env))
		return (1);
	return (0);
}

void			ft_sti(t_process *process, t_environment *env)
{
	int	counter_swipe;
	int	tmp;
	int	tmp2;

	counter_swipe = count_swipe(process, env);
	tmp = (process->command_cache->codage[1] == 'R') ?
		conv_mem(return_arg(process, env, 1)) :
		convert_arg(return_arg(process, env, 1), process, 1);
	tmp = (process->command_cache->codage[1] == 'I') ?
		conv_mem(return_arg(process, env, 1)) : tmp;
	tmp2 = (process->command_cache->codage[2] == 'R') ?
		conv_mem(return_arg(process, env, 2)) :
		convert_arg(return_arg(process, env, 2), process, 2);
	n_cpy_map(env, return_arg(process, env, 0),
			return_ind(get_adr(process->program_counter,
	(tmp + tmp2) % IDX_MOD, env), env), 4);
	log_event(process, get_adr(env->map,
							return_ind(get_adr(process->program_counter,
	(tmp + tmp2) % IDX_MOD, env), env), env), env, 4);
	process->program_counter = get_adr(process->program_counter,
									counter_swipe, env);
	process->success = 1;
	set_delay(process);
}
