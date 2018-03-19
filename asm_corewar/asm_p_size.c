/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_p_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:35:02 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:35:03 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool			asm_check_label_same(t_ins *ins, char *label)
{
	t_list	*tmp;
	char	*str;

	tmp = ins->label;
	while (tmp)
	{
		str = tmp->content;
		if (ft_strcmp(label, str) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

unsigned int	asm_get_adress_label(t_asm *data, char *label, unsigned int pos)
{
	t_list			*tmp;
	t_ins			*ins;
	unsigned int	adress;

	adress = 0;
	tmp = data->ins;
	while (tmp)
	{
		ins = tmp->content;
		if (ins->label && asm_check_label_same(ins, label))
			return (adress - pos);
		adress += (ins->size);
		tmp = tmp->next;
	}
	asm_error("No label\n");
	return (0);
}

void			asm_set_label_value(t_asm *data, t_ins *ins, unsigned int pos)
{
	t_list	*tmp;
	t_param	*p;

	tmp = ins->param;
	while (tmp)
	{
		p = tmp->content;
		(p->label) ? p->value = asm_get_adress_label(data, p->label, pos) : 1;
		tmp = tmp->next;
	}
}

void			asm_get_prog_size(t_asm *data)
{
	t_list			*tmp;
	t_ins			*ins;
	unsigned int	size;

	size = 0;
	tmp = data->ins;
	while (tmp)
	{
		ins = tmp->content;
		asm_set_label_value(data, ins, size);
		size += (ins->size);
		tmp = tmp->next;
	}
	data->header->prog_size = size;
}
