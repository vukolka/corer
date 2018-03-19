/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_ins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:38:55 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:38:56 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_print_param(t_ins *ins, int fd)
{
	t_list	*tmp;
	t_param	*tmp_param;

	tmp = ins->param;
	while (tmp)
	{
		tmp_param = tmp->content;
		if (tmp_param->type == T_REG)
			asm_print_uint_hex(fd, tmp_param->value, 1);
		else if (tmp_param->type == 3)
			asm_print_uint_hex(fd, tmp_param->value, 2);
		else if (tmp_param->type == T_DIR && ins->two_bytes)
			asm_print_uint_hex(fd, tmp_param->value, 2);
		else if (tmp_param->type == T_DIR && ins->two_bytes == false)
			asm_print_uint_hex(fd, tmp_param->value, 4);
		tmp = tmp->next;
	}
	return (0);
}

void	asm_print_ins(t_asm *data, int fd)
{
	t_list	*tmp;
	t_ins	*tmp_ins;

	tmp = data->ins;
	while (tmp)
	{
		tmp_ins = tmp->content;
		if (tmp_ins->opcode == 0)
			return ;
		write(fd, &(tmp_ins->opcode), 1);
		(tmp_ins->coding_byte) ? write(fd, &(tmp_ins->coding_byte), 1) : 1;
		asm_print_param(tmp_ins, fd);
		tmp = tmp->next;
	}
}
