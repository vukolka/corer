/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:11:31 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:11:32 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int			set_zero(t_environment *env)
{
	t_llist *t;

	t = (t_llist *)env->players;
	while (t)
	{
		((t_player *)t->content)->current_lives = 0;
		t = t->next;
	}
}

void		get_winner(t_environment *env)
{
	t_player	*winner;
	t_llist		*players;

	players = (t_llist *)env->players;
	winner = ((t_player *)players->content);
	while (players)
	{
		if (winner->last_live_cycle <
				((t_player *)players->content)->last_live_cycle)
			winner = ((t_player *)players->content);
		players = players->next;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n",
		winner->id,
		winner->name);
}

void		end_game(t_environment *env, int end)
{
	close(env->fd);
	close(env->debug_fd);
	if (end)
		get_winner(env);
	exit(0);
}

void		delete_proc(t_process **proc)
{
	(*proc)->program_counter = NULL;
	if ((*proc)->command_cache->codage)
		free((*proc)->command_cache->codage);
	free((*proc)->command_cache->args[2]);
	free((*proc)->command_cache->args[1]);
	free((*proc)->command_cache->args[0]);
	free((*proc)->command_cache->args);
	free((*proc)->command_cache);
	free(*proc);
}
