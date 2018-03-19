/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:29:14 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 17:29:21 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft/classes_lib/linked_list.h"
#include "op.h"
#include <fcntl.h>

void	log_state(t_environment *environment)
{
	int		fd;
	t_llist	*temp;

	temp = environment->players;
	fd = environment->fd;
	ft_printf_fd("<players>\n", fd);
	while (temp)
	{
		ft_printf_fd("[<%d> <%d> <%d>]\n", fd,
			((t_player *)(temp->content))->id,
			((t_player *)(temp->content))->current_lives,
			((t_player *)(temp->content))->last_live_cycle);
		temp = temp->next;
	}
	ft_printf_fd("</players>\n<processes>\n", fd);
	while_in_logstate(environment);
	ft_printf_fd("</processes>\n", fd);
}

void	log_event(t_process *process, unsigned char *destination_adr,
					t_environment *environment, int n)
{
	int fd;
	int i;

	i = 0;
	fd = environment->fd;
	if (!environment->vis_flag)
		return ;
	ft_printf_fd("[<%d> <%d> ", fd,
				process->player_id,
				return_ind(destination_adr, environment));
	while (i < n)
	{
		ft_printf_fd("<%d> ", fd, *(destination_adr + i));
		i++;
	}
	ft_printf_fd("]\n", fd);
}
