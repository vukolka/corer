/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:16:22 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:16:22 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

char			**count_players(char **str, int num, int *pl_count)
{
	int		i;
	int		k;
	char	**player_list;

	i = 1;
	k = 0;
	player_list = (char **)ft_memalloc(sizeof(char *) * 4);
	while (i < num)
	{
		if (ft_strstr(str[i], ".cor") &&
			!(str[i][ft_strstr(str[i], ".cor") - str[i] + 4]))
		{
			player_list[k] = ft_strdup(str[i]);
			(*pl_count)++;
			k++;
		}
		if (ft_strchr(str[i], '.') && !ft_strstr(str[i], ".cor"))
			ft_printf_last_error("Invalid input");
		i++;
	}
	if (!*pl_count || *pl_count > MAX_PLAYERS)
		ft_printf_last_error("Invalid player");
	return (player_list);
}

unsigned char	*free_join(unsigned char *old, char *new)
{
	unsigned char *tmp;

	tmp = old;
	old = (unsigned char *)ft_strjoin(old, new);
	free(tmp);
	return (old);
}

void			get_name_and_desc(int fd, t_player *player)
{
	unsigned char *str;

	str = ft_memalloc(sizeof(unsigned char) * 5);
	read(fd, str, 4);
	player->name = ft_memalloc(1);
	player->description = ft_memalloc(1);
	while (1)
	{
		read(fd, str, 4);
		if (str[3] == 0 && str[2] == 0 && str[0] == 0 && str[1] == 0)
			break ;
		player->name = free_join(player->name, str);
	}
	while (str[3] == 0 && str[2] == 0 && str[0] == 0 && str[1] == 0)
		read(fd, str, 4);
	player->size = conv_mem(str);
	while (1)
	{
		read(fd, str, 4);
		player->description = free_join(player->description, str);
		if (str[3] == 0 && str[2] == 0 && str[0] == 0 && str[1] == 0)
			break ;
	}
	free(str);
}

void			put_player_ints(t_player *player, int i)
{
	player->id = i + 1;
	player->last_live_cycle = 0;
	player->current_lives = 0;
}

int				add_to_map(int fd, t_environment *env, int ind, int pl_count)
{
	unsigned char	*str;
	int				i;
	int				k;
	int				size;

	size = 0;
	i = MEM_SIZE - ((MEM_SIZE / pl_count) * (pl_count - ind));
	str = ft_memalloc(sizeof(unsigned char) * 5);
	while ((read(fd, str, 4)))
		if (!(str[3] == 0 && str[2] == 0 && str[0] == 0 && str[1] == 0))
			break ;
	k = 0;
	while (k < 4)
		env->map[i++] = str[k++];
	while (i < MEM_SIZE)
	{
		if (!(read(fd, str, 1)))
			break ;
		env->map[i++] = *str;
		size++;
	}
	free(str);
	return (size + 4);
}
