/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_processing4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:07:14 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:07:15 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include <libft.h>
#include <ft_printf/ft_printf.h>
#include "op.h"
#include "../libft/classes_lib/linked_list.h"
#include "../libft/classes_lib/queue.h"

void			n_cpy_map(t_environment *env, unsigned char *src,
						int start, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		*get_adr(env->map, (i + start), env) = src[i];
		i++;
	}
}

void			n_cpy_reg(t_process *process, unsigned char *src,
						unsigned char *start, int count)
{
	int i;

	i = 0;
	while (i < count && start != process->memory + (REG_SIZE * REG_NUMBER))
	{
		start[i] = src[i];
		i++;
	}
}

int				valid_aff(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (process->command_cache->codage[0] == 'R' &&
		check_val_regs(process, env))
		return (1);
	return (0);
}

void			ft_aff(t_process *process, t_environment *env)
{
	int i;

	i = 0;
	while (i < REG_SIZE)
	{
		ft_printf("%c", return_arg(process, env, 0)[i] % 128);
		i++;
	}
	ft_printf("\n");
	process->program_counter = get_adr(process->program_counter, 3, env);
	process->success = 1;
	set_delay(process);
}

int				valid_ld(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (process->command_cache->codage[1] == 'R' &&
		(process->command_cache->codage[0] == 'I' ||
		process->command_cache->codage[0] == 'D')
		&& process->command_cache->codage[2] == 'N'
		&& check_val_regs(process, env))
		return (1);
	return (0);
}
