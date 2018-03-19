/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:29:37 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 17:29:39 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/ft_printf.h"
#include "../libft/classes_lib/linked_list.h"
#include "op.h"
#include <fcntl.h>

void	print_movement(t_process *proc,
						t_environment *env, int ind, int count)
{
	int swipe;
	int i;

	i = 0;
	if (ind)
	{
		if (g_op_tab[proc->command_cache->op_code - 1].codage)
			swipe = count_swipe(proc, env);
		else
			swipe = (proc->command_cache->op_code <= 16 &&
			proc->command_cache->op_code > 0) ? 1 +
			g_op_tab[proc->command_cache->op_code - 1].lable_size : 2;
		ft_printf_fd("ADV %d (%#.4x -> %#.4x)", env->debug_fd,
			swipe, return_ind(proc->program_counter, env) % MEM_SIZE,
			return_ind(proc->program_counter + swipe, env) % MEM_SIZE);
		while (i < swipe)
			ft_printf_fd(" %.2x", env->debug_fd,
						*get_adr(proc->program_counter, i++, env));
	}
	else
		ft_printf_fd("ADV %d (%#.4x -> %#.4x)",
			env->debug_fd, count, return_ind(proc->program_counter,
			env) % MEM_SIZE, return_ind(proc->program_counter + count,
			env) % MEM_SIZE);
	ft_printf_fd("\n", env->debug_fd);
}

void	debug_log(t_process *proc, t_environment *env, int success)
{
	if (!env->debug_flag)
		return ;
	if (proc->success)
		print_operation(proc, env);
	if (proc->success && proc->command_cache->op_code != 9)
		print_movement(proc, env, 1, 0);
}

void	init_log(t_environment *environment)
{
	int		i;
	int		fd;
	t_llist	*temp;

	i = 0;
	temp = environment->players;
	fd = environment->fd;
	ft_printf_fd("<players descr>\n", fd);
	while (temp)
	{
		ft_printf_fd("[<%d> <%s> <%s>]\n", fd,
			((t_player *)(temp->content))->id,
			((t_player *)(temp->content))->name,
			((t_player *)(temp->content))->description);
		temp = temp->next;
	}
	ft_printf_fd("</players descr>\n", fd);
	fd = open("../map.txt", O_RDWR | O_APPEND);
	while (i < MEM_SIZE)
		ft_printf_fd("%c", fd, environment->map[i++]);
	log_state(environment);
}

int		return_ind(unsigned char *adr, t_environment *environment)
{
	return ((adr - environment->map) % MEM_SIZE);
}

void	while_in_logstate(t_environment *environment)
{
	t_process *head;

	head = environment->processes_queue;
	while (environment->processes_queue)
	{
		ft_printf_fd("[<%d> <%d> <%d>]\n", environment->fd,
		environment->processes_queue->player_id,
		environment->processes_queue->program_counter - environment->map,
		environment->processes_queue->live_executions);
		environment->processes_queue = environment->processes_queue->next;
	}
	environment->processes_queue = head;
}
