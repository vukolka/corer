/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:29:29 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 17:29:31 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/ft_printf.h"
#include "../libft/classes_lib/linked_list.h"
#include "op.h"
#include <fcntl.h>

void	trunc_log(void)
{
	int fd;

	fd = open("../log.txt", O_CREAT | O_TRUNC, S_IRWXU);
	close(fd);
	fd = open("../map.txt", O_CREAT | O_TRUNC, S_IRWXU);
	close(fd);
	fd = open("../debug_log.txt", O_CREAT | O_TRUNC, S_IRWXU);
	close(fd);
}

void	dump_memory(t_environment *env)
{
	int i;
	int k;

	i = 0;
	while (i < 64)
	{
		k = 0;
		ft_printf("%#4.4x :", 64 * i);
		while (k < 64)
		{
			ft_printf(" %2.2x", env->map[(64 * i) + k]);
			k++;
		}
		i++;
		ft_printf("\n");
	}
	end_game(env, 0);
}

void	sti_dop_print(t_process *proc, t_environment *env)
{
	short tmp;
	short tmp2;

	get_args(proc->command_cache, proc->program_counter, env);
	tmp = (proc->command_cache->codage[1] == 'R') ?
			(short)conv_mem(return_arg(proc, env, 1)) :
			(short)convert_arg(return_arg(proc, env, 1), proc, 1);
	tmp = (proc->command_cache->codage[1] == 'I') ?
			(short)conv_mem(return_arg(proc, env, 1)) : tmp;
	tmp2 = (proc->command_cache->codage[2] == 'R') ?
			(short)conv_mem(return_arg(proc, env, 2)) :
			(short)convert_arg(return_arg(proc, env, 2), proc, 2);
	ft_printf_fd("	  | -> store to %d + %d = %d (with pc and mod %d)\n",
				env->debug_fd, tmp, tmp2, tmp + tmp2,
				(tmp + tmp2) % IDX_MOD + proc->program_counter - env->map);
}

void	print_op_inside(t_process *proc, t_environment *env)
{
	int i;

	i = 0;
	while (i < g_op_tab[proc->command_cache->op_code - 1].args_num)
	{
		if (proc->command_cache->codage[i] == 'N')
			break ;
		if (proc->command_cache->codage[i] == 'R')
			ft_printf_fd(" r%hd", env->debug_fd, *proc->command_cache->args[i]);
		else if (proc->command_cache->codage[i] == 'D')
			ft_printf_fd(" %hd", env->debug_fd,
						convert_arg(proc->command_cache->args[i], proc, i));
		else if (proc->command_cache->codage[i] == 'I')
			ft_printf_fd(" %d", env->debug_fd,
						conv_mem(proc->command_cache->args[i]));
		i++;
	}
}

void	print_operation(t_process *proc, t_environment *env)
{
	ft_printf_fd("P	%d | %s", env->debug_fd, proc->id,
				g_op_tab[proc->command_cache->op_code - 1].name);
	print_op_inside(proc, env);
	if (proc->command_cache->op_code == 9)
		if (proc->carry == 1)
			ft_printf_fd(" OK", env->debug_fd);
		else
			ft_printf_fd(" FAIL", env->debug_fd);
	if (proc->command_cache->op_code == 12 ||
			proc->command_cache->op_code == 15)
		ft_printf_fd(" (%hd)", env->debug_fd,
		((short)convert_arg(proc->command_cache->args[0],
		proc, 0) + proc->program_counter) - env->map);
	ft_printf_fd("\n", env->debug_fd);
	if (proc->command_cache->op_code == 11)
		sti_dop_print(proc, env);
}
