/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pars1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:16:17 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:16:18 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf/libftprintf/libft.h"
#include "../libft/classes_lib/linked_list.h"
#include "../libft/ft_printf/ft_printf/ft_printf.h"
#include "../libft/classes_lib/new.h"
#include "op.h"

int				get_player(int fd, t_environment *env, int i, int pl_count)
{
	t_player *player;

	player = (t_player *)ft_memalloc(sizeof(t_player));
	get_name_and_desc(fd, player);
	put_player_ints(player, i);
	llst_add(&env->players, new(g_list, player));
	if (add_to_map(fd, env, i, pl_count) != player->size
		|| player->size > CHAMP_MAX_SIZE || player->size == 0)
		ft_printf_last_error("Incorrect player size");
	return (1);
}
