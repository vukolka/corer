/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:56:32 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 17:56:35 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include "op.h"
#include "../libft/classes_lib/new.h"
#include "../libft/classes_lib/queue.h"
#include "../libft/classes_lib/linked_list.h"
#include "../libft/ft_printf/libftprintf/libft.h"

unsigned char	*get_args_helper(t_environment *env,
								t_command_cache *p_cache,
								unsigned char *counter)
{
	if (g_op_tab[p_cache->op_code - 1].codage)
		counter = get_adr(counter, 2, env);
	else
		counter = get_adr(counter, 1, env);
	return (counter);
}

void			get_args(t_command_cache *p_cache,
						unsigned char *counter, t_environment *env)
{
	int		i;
	size_t	k;
	int		a;

	i = 1;
	counter = get_args_helper(env, p_cache, counter);
	while (i <= g_op_tab[p_cache->op_code - 1].args_num)
	{
		k = 0;
		a = 0;
		if (p_cache->codage[i - 1] == 'I')
			k += 2;
		else if (p_cache->codage[i - 1] == 'D'
				|| !g_op_tab[p_cache->op_code - 1].codage)
			k += g_op_tab[p_cache->op_code - 1].lable_size;
		else if (p_cache->codage[i - 1] == 'R')
			k++;
		while (a < k)
		{
			p_cache->args[i - 1][a] = *(counter + a);
			a++;
		}
		counter = get_adr(counter, k, env);
		i++;
	}
}

void			make_move(t_process *curr_process, t_environment *env)
{
	t_command_cache *cache;

	cache = curr_process->command_cache;
	if (cache->cycles_left > 0)
	{
		cache->cycles_left--;
		return ;
	}
	else if (cache->cycles_left == 0)
	{
		if (g_op_tab[(curr_process->command_cache->op_code) - 1].codage)
			curr_process->command_cache->codage =
					decode_codage(curr_process->command_cache,
						curr_process->program_counter, env);
		else
			curr_process->command_cache->codage = ft_strdup("DNN");
		process_operation(curr_process, env);
		return ;
	}
	if (cache->op_code == 0)
	{
		just_skip(curr_process, env);
		return ;
	}
}

void			make_turn(t_environment *environment)
{
	t_process		*temp_queue;
	t_process		*current_process;

	environment->cycles += 1;
	temp_queue = NULL;
	if (environment->vis_flag)
		ft_printf_fd("<cycle>\n[<%d> <%d>]\n</cycle>\n<events>\n",
					environment->fd,
	environment->cycles, environment->cyclestodie);
	while (environment->processes_queue)
	{
		current_process = get_from_head(&(environment->processes_queue));
		if (!current_process->new)
		{
			make_move(current_process, environment);
			add_to_tail(current_process, &temp_queue);
		}
		else
			add_to_head(current_process, &temp_queue);
		current_process->new = 0;
	}
	if (environment->vis_flag)
		ft_printf_fd("</events>\n", environment->fd);
	free(environment->processes_queue);
	environment->processes_queue = temp_queue;
}
