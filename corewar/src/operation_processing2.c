/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_processing2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:05:19 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:05:19 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void			ft_and(t_process *process, t_environment *env)
{
	int				counter_swipe;
	int				i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	counter_swipe = count_swipe(process, env);
	while (i < 4)
	{
		tmp1 = return_arg(process, env, 0);
		tmp2 = return_arg(process, env, 1);
		return_arg(process, env, 2)[i] = tmp1[i] & tmp2[i];
		i++;
	}
	process->carry = conv_mem(return_arg(process, env, 2)) ? 0 : 1;
	process->program_counter =
			get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

void			ft_or(t_process *process, t_environment *env)
{
	int				counter_swipe;
	int				i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	counter_swipe = count_swipe(process, env);
	while (i < 4)
	{
		tmp1 = return_arg(process, env, 0);
		tmp2 = return_arg(process, env, 1);
		return_arg(process, env, 2)[i] = tmp1[i] | tmp2[i];
		i++;
	}
	process->carry = conv_mem(return_arg(process, env, 2)) ? 0 : 1;
	process->program_counter =
			get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

void			ft_xor(t_process *process, t_environment *env)
{
	int				counter_swipe;
	int				i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	counter_swipe = count_swipe(process, env);
	i = 0;
	while (i < 4)
	{
		tmp1 = return_arg(process, env, 0);
		tmp2 = return_arg(process, env, 1);
		return_arg(process, env, 2)[i] = tmp1[i] ^ tmp2[i];
		i++;
	}
	process->carry = conv_mem(return_arg(process, env, 2)) ? 0 : 1;
	process->program_counter =
			get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

unsigned char	*deconvert_arg(int num)
{
	unsigned char	*res;
	int				temp;

	res = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
	temp = num;
	res[0] = (unsigned char)(temp >> 24);
	temp = num;
	res[1] = (unsigned char)(((temp << 8) >> 24));
	temp = num;
	res[2] = (unsigned char)(((temp << 16) >> 24));
	temp = num;
	res[3] = (unsigned char)(((temp << 24) >> 24));
	return (res);
}

void			ft_sub(t_process *process, t_environment *env)
{
	int				temp;
	unsigned char	*dec;

	temp = conv_mem(return_arg(process, env, 0))
		- conv_mem(return_arg(process, env, 1));
	dec = deconvert_arg(temp);
	n_cpy_reg(process, dec, return_arg(process, env, 2), 4);
	process->carry = (temp) ? 0 : 1;
	process->program_counter = get_adr(process->program_counter, 5, env);
	process->success = 1;
	free(dec);
	set_delay(process);
}
