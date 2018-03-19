/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:54:14 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 17:54:24 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void			add_to_tail(t_process *new, t_process **list)
{
	t_process *head;

	head = *list;
	if (!*list)
	{
		*list = new;
		return ;
	}
	while ((*list)->next)
		(*list) = (*list)->next;
	new->next = NULL;
	(*list)->next = new;
	*list = head;
}

void			add_to_head(t_process *new, t_process **list)
{
	new->next = *list;
	*list = new;
}

t_process		*get_from_head(t_process **list)
{
	t_process *temp;

	temp = *list;
	*list = (*list)->next;
	temp->next = NULL;
	return (temp);
}

unsigned char	*get_adr(unsigned char *adr, int ind, t_environment *env)
{
	int moved;
	int delta;

	moved = 0;
	ind = ind % MEM_SIZE;
	delta = (ind >= 0) ? 1 : -1;
	while (moved != ind)
	{
		if (adr + delta - env->map < MEM_SIZE && adr + delta - env->map >= 0)
			adr += delta;
		else
			adr += (delta > 0) ? (-MEM_SIZE + 1) : (MEM_SIZE - 1);
		moved += delta;
	}
	return (adr);
}

char			*decode_codage(t_command_cache *p_cache,
					unsigned char *counter, t_environment *env)
{
	char			*ret;
	unsigned char	codage;
	char			*a;

	codage = *get_adr(counter, 1, env);
	a = "NRDI";
	ret = ft_memalloc(4 * sizeof(char));
	if (g_op_tab[p_cache->op_code - 1].codage)
	{
		ret[0] = a[codage >> 6];
		ret[1] = a[(codage & 0b00110000) >> 4];
		ret[2] = a[(codage & 0b00001100) >> 2];
	}
	else
		ret = ft_strdup("DNN");
	return (ret);
}
