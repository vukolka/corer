/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:04:06 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:04:07 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int				count_swipe(t_process *proc, t_environment *env)
{
	int swipe;
	int i;

	i = 0;
	swipe = (g_op_tab[proc->command_cache->op_code - 1].codage) ? 2 : 1;
	while (i < g_op_tab[proc->command_cache->op_code - 1].args_num)
	{
		if (proc->command_cache->codage[i] == 'D')
			swipe += g_op_tab[*proc->program_counter - 1].lable_size;
		else if (proc->command_cache->codage[i] == 'I')
			swipe += 2;
		else if (proc->command_cache->codage[i] == 'R')
			swipe += 1;
		i++;
	}
	return (swipe);
}

int				convert_arg(unsigned char *arg, t_process *proc, int num)
{
	int				res;
	unsigned int	temp;

	temp = arg[0];
	res = temp << 24;
	temp = arg[1];
	res = res | (temp << 16);
	temp = arg[2];
	res = res | (temp << 8);
	temp = arg[3];
	res = res | (temp);
	if (proc->command_cache->codage[num] == 'D')
		res = res >> ((4 -
			g_op_tab[proc->command_cache->op_code - 1].lable_size) * 8);
	else if (proc->command_cache->codage[num] == 'I')
	{
		res = res >> 16;
		return ((res));
	}
	else
		res = res >> 24;
	return (res);
}

int				conv_mem(unsigned char *arg)
{
	int				res;
	unsigned int	temp;

	temp = arg[0];
	res = temp << 24;
	temp = arg[1];
	res = res | (temp << 16);
	temp = arg[2];
	res = res | (temp << 8);
	temp = arg[3];
	res = res | (temp);
	return (res);
}

unsigned char	*return_arg(t_process *proc, t_environment *env, int ind)
{
	if (proc->command_cache->codage[ind] == 'D')
		return (proc->command_cache->args[ind]);
	else if (proc->command_cache->codage[ind] == 'R')
		return (&proc->memory[convert_arg(proc->command_cache->args[ind],
			proc, ind) * (REG_SIZE) - 4]);
	else if (proc->command_cache->codage[ind] == 'I'
			&& (proc->command_cache->op_code != 3))
		return (get_adr(proc->program_counter,
				convert_arg(proc->command_cache->args[ind], proc, ind), env));
	else if (proc->command_cache->codage[ind] == 'I')
		return (proc->command_cache->args[ind]);
	return (0);
}
