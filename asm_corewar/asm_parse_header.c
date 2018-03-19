/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:37:38 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:37:39 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	asm_newline(char *str, char *line, int len)
{
	if ((int)ft_strlen(str) + (int)ft_strlen(line) + 1 < len)
	{
		ft_strcat(str, line);
		ft_strcat(str, "\n");
	}
	else if ((int)ft_strlen(line) + 1 > len)
		asm_error("wrong header\n");
}

static void	asm_end_q(char *str, char *line, int fd, int len)
{
	int	i;

	asm_newline(str, line, len);
	while (get_next_line(fd, &line) && i < len)
	{
		i = 0;
		while (line[i] && line[i] != '\"')
			i++;
		if (line[i] && (int)ft_strlen(str) + i < len)
		{
			ft_strncat(str, line, i);
			if (line[i + 1])
				(asm_blank(&(line[i + 1]))) ? asm_error("wrong header\n") : 1;
			return ;
		}
		else if ((int)ft_strlen(str) > len)
			asm_error("wrong header\n");
		asm_newline(str, line, len);
	}
}

static void	asm_parse_header_value(char *str, char *line, int fd, int len)
{
	int		i;

	i = 0;
	while (*line == ' ' || *line == '\t')
		line++;
	(*line != '\"') ? asm_error("wrong header!\n") : 1;
	line++;
	while (line[i] && line[i] != '\"')
		i++;
	if (line[i] && i < len)
	{
		ft_strncat(str, line, i);
		(line[i + 1]) ? asm_error("wrong header!\n") : 1;
	}
	else if (i > len)
		asm_error("wrong header!\n");
	else
		asm_end_q(str, line, fd, len);
}

void		asm_parse_header(t_asm *data, int fd)
{
	char *str;

	while (get_next_line(fd, &str))
	{
		while (*str == ' ' || *str == '\t')
			str++;
		if (*str == '#' || !(*str))
			continue;
		if (!(*data->header->prog_name) && ft_strncmp(str, ".name", 5) == 0)
		{
			str += 5;
			asm_parse_header_value(data->header->prog_name,
				str, fd, PROG_NAME_LENGTH);
		}
		else if (!(*data->header->comment) &&
		ft_strncmp(str, ".comment", 8) == 0)
		{
			str += 8;
			asm_parse_header_value(data->header->comment,
				str, fd, COMMENT_LENGTH);
			break ;
		}
		else
			asm_error("no name or comment\n");
	}
}
