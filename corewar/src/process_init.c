/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:15:44 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:15:45 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		get_id(t_environment *env, int ind)
{
	t_llist	*t;
	int		i;

	i = 1;
	t = (t_llist *)env->players;
	while (i < env->pl_count - ind)
	{
		i++;
		t = t->next;
	}
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
	((t_player *)t->content)->id,
	((t_player *)t->content)->size,
	((t_player *)t->content)->name,
	((t_player *)t->content)->description);
	return (((t_player *)t->content)->id);
}

void	process_init(t_environment *env, int i, int pl_count)
{
	t_process *process;

	process = (t_process *)ft_memalloc(sizeof(t_process));
	ft_bzero(process->memory, REG_NUMBER * REG_SIZE + 1);
	ft_memset(process->memory, 0xff, 4);
	process->memory[3] = (unsigned char)-(i + 1);
	process->carry = 0;
	process->new = 0;
	process->live_executions = 0;
	process->program_counter =
			&(env->map[MEM_SIZE - ((MEM_SIZE / pl_count) * (pl_count - i))]);
	malloc_cache(process);
	process->player_id = (unsigned)get_id(env, i);
	process->id = i + 1;
	add_to_head(process, &env->processes_queue);
	set_delay(process);
}
