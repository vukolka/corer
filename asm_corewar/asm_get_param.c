/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:33:05 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:33:06 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_param	*asm_get_tparam(char *str)
{
	t_param		*p;
	int			i;

	i = 0;
	p = (t_param *)malloc(sizeof(t_param));
	p->type = 0;
	if (str[i] == '%')
	{
		p->type = T_DIR;
		i++;
	}
	if (!str[i])
		asm_error("Wrong parameter\n");
	if (str[i] == 'r')
		asm_get_reg_param(p, str);
	else if (str[i] == ':')
		asm_get_label_param(p, str);
	else if (ft_isdigit(str[i]) || str[i] == '-')
		asm_get_num_param(p, str);
	else
		asm_error("Wrong parameter\n");
	return (p);
}

bool	asm_check_com(char **tab)
{
	int i;
	int	last;

	i = 0;
	if (tab[i][0] == ',')
		return (true);
	i++;
	while (tab[i])
	{
		last = ft_strlen(tab[i - 1]);
		if (tab[i][0] == '#' && tab[i - 1][last - 1] == ',')
			return (true);
		else if (tab[i][0] == '#')
			return (false);
		if (tab[i][0] != ',' && tab[i - 1][last - 1] != ',')
			return (true);
		i++;
	}
	return (false);
}

void	asm_get_ins_param(t_ins *ins, char **tab)
{
	t_param		*par;
	char		**ntab;

	if (asm_check_com(tab))
		asm_error("Wrong parameter\n");
	while (*tab)
	{
		if (*tab[0] == COMMENT_CHAR || *tab[0] == ';')
			return ;
		ntab = ft_strsplit(*tab, ',');
		while (*ntab)
		{
			par = asm_get_tparam(*ntab);
			if (ins->param == NULL)
				ins->param = ft_lstnew(par, sizeof(t_param));
			else
				ft_lstappend(&(ins->param), ft_lstnew(par, sizeof(t_param)));
			ntab++;
		}
		tab++;
	}
}
