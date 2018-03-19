/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_ins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:32:44 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:32:46 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool	asm_check_opcode(t_ins *new_ins, char **tab, t_op g_op_tab[17])
{
	int i;

	i = 0;
	while (i < 16 && *tab)
	{
		if (ft_strcmp(g_op_tab[i].name, *tab) == 0
		&& ft_strlen(*tab) == ft_strlen(g_op_tab[i].name))
		{
			tab++;
			if (!(*tab))
				return (false);
			new_ins->op_code = g_op_tab[i];
			new_ins->opcode = g_op_tab[i].opcode;
			asm_get_ins_param(new_ins, tab);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	asm_get_label_ins(t_ins *ins, char *str)
{
	int i;

	i = 0;
	while (str[i] && asm_valid_label_char(str[i], LABEL_CHARS))
		i++;
	if (str[i] == LABEL_CHAR && i == (int)ft_strlen(str) - 1)
	{
		str[i] = '\0';
		if (ins->label == NULL)
			ins->label = ft_lstnew(str, i + 1);
		else
			ft_lstappend(&(ins->label), ft_lstnew(str, i + 1));
		return (true);
	}
	return (false);
}

void	asm_get_ins_line(t_ins *ins, char *line, t_op g_op_tab[17])
{
	char	**tab;
	int		i;
	bool	is_label;

	i = 0;
	tab = asm_split_line(line);
	while (tab[i])
	{
		if (tab[i][0] == '#')
			return ;
		is_label = asm_get_label_ins(ins, tab[i]);
		if (!is_label)
			if (asm_check_opcode(ins, tab + i, g_op_tab))
				return ;
		if (!is_label)
			asm_error("Wrong instruction\n");
		i++;
	}
}
