/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:34:37 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:34:38 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				main(int argc, char **argv)
{
	t_asm	*data;
	int		len;
	int		fd;

	(argc != 2) ? asm_error("wrong number of args\n") : 1;
	(!(data = (t_asm *)malloc(sizeof(t_asm)))) ?
	asm_error("malloc error!\n") : 1;
	len = ft_strlen(argv[1]);
	(len < 3 || argv[1][len - 1] != 's' || argv[1][len - 2] != '.') ?
	asm_error("wrong file name\n") : 1;
	asm_data_init(data);
	((fd = open(argv[1], O_RDONLY)) < 0) ? asm_error("no such file") : 1;
	asm_parse_header(data, fd);
	asm_parse_instruction(data, fd);
	asm_check_ins(data);
	asm_get_prog_size(data);
	asm_print_bytecode(data, argv[1]);
	return (0);
}
