/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:33:33 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:33:34 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool	asm_blank(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == ',')
		str++;
	if (!(*str))
		return (false);
	if (*str == ',')
		return (false);
	else
		return (true);
}

char	**asm_split_line(char *line)
{
	char	**tab;
	int		i;

	i = 0;
	while (line[i])
	{
		(line[i] == '\t') ? line[i] = ' ' : 1;
		i++;
	}
	tab = ft_strsplit(line, ' ');
	return (tab);
}

void	asm_error(char *message)
{
	ft_putstr(message);
	exit(0);
}

bool	asm_valid_label_char(char c, char *label_chars)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(label_chars))
	{
		if (label_chars[i] != c)
			i++;
		else
			return (true);
	}
	return (false);
}

bool	asm_is_com(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '#')
		return (true);
	return (false);
}
