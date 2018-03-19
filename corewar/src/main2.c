/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:36:46 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 17:36:48 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <zconf.h>
#include "op.h"
#include "../libft/ft_printf/libftprintf/libft.h"
#include "../libft/classes_lib/classes_lib.h"
#include "../libft/ft_printf/ft_printf/ft_printf.h"
#include "../libft/classes_lib/linked_list.h"

void	ft_printf_last_error(char *err)
{
	ft_printf("%s\n", err);
	exit(0);
}

int		valid_num(char *num)
{
	char	*temp;
	int		n;

	if (!num)
		return (0);
	n = ft_atoi(num);
	temp = ft_itoa(n);
	if (ft_strlen(num) == ft_strlen(temp))
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

void	count_dich(int *i, int *count, char **flags)
{
	while (*i >= 0 && !ft_strequ("-n", flags[*i]))
		(*i)--;
	if (*i >= 0 && ft_strequ("-n", flags[*i]))
		(*count)++;
}

void	player_num(char **flags, int pl_count, t_environment *env)
{
	int		count;
	t_llist	*pl_list;
	int		i;

	i = 0;
	count = 0;
	while (flags[i + 1])
		i++;
	pl_list = (t_llist *)env->players;
	while (pl_list)
	{
		count_dich(&i, &count, flags);
		if (flags[i + 1] && valid_num(flags[i + 1]))
		{
			((t_player *)pl_list->content)->id =
					(unsigned)ft_atoi(flags[i + 1]);
			i--;
			pl_count--;
		}
		else if (count)
			ft_printf_last_error("incorrect -n");
		pl_list = pl_list->next;
	}
	if (pl_count && count)
		ft_printf_last_error("incorrect -n");
}
