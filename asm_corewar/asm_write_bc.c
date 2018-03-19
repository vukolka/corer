/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_bc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:38:43 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:38:43 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_print_uint_hex(int fd, unsigned int nb, char l)
{
	unsigned int	b;

	b = 0;
	while (l > 4)
	{
		write(fd, &b, 1);
		l--;
	}
	if (l >= 4)
	{
		b = (nb & MASK1) >> 24;
		write(fd, &b, 1);
		b = (nb & MASK2) >> 16;
		write(fd, &b, 1);
	}
	if (l >= 2)
	{
		b = (nb & MASK3) >> 8;
		write(fd, &b, 1);
	}
	b = (nb & MASK4);
	write(fd, &b, 1);
}

void	asm_print_header(t_asm *data, int fd)
{
	t_header	*h;
	int			i;

	i = 0;
	h = data->header;
	asm_print_uint_hex(fd, h->magic, 4);
	while (i < PROG_NAME_LENGTH + 4)
	{
		(h->prog_name[i] && i < (int)ft_strlen(h->prog_name)) ?
			write(fd, &(h->prog_name[i]), 1) : asm_print_uint_hex(fd, 0, 1);
		i++;
	}
	i = 0;
	asm_print_uint_hex(fd, h->prog_size, 4);
	while (i < COMMENT_LENGTH + 4)
	{
		(h->comment[i] && i < (int)ft_strlen(h->comment)) ?
		write(fd, &(h->comment[i]), 1) : asm_print_uint_hex(fd, 0, 1);
		i++;
	}
}

char	*asm_get_name(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (str[i] && str[i] != '.')
		i--;
	if (!str[i])
		return (str);
	return (ft_strsub(str, 0, i));
}

void	asm_print_bytecode(t_asm *data, char *name)
{
	int fd;

	fd = open(ft_strcat(asm_get_name(name), ".cor"),
	O_WRONLY | O_CREAT | O_TRUNC, 0777);
	asm_print_header(data, fd);
	asm_print_ins(data, fd);
	ft_putstr("Writing out to ");
	ft_putstr(ft_strcat(asm_get_name(name), ".cor"));
	ft_putchar('\n');
}
