/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:31:22 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:31:23 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_check_param_value(t_ins *ins, t_op opcode, t_param *param, int i)
{
	(param->type == 3 && !(opcode.param[i] & 4)) ?
	asm_error("Wrong argument\n") : 1;
	(!(param->type & opcode.param[i])) ? asm_error("Wrong argument\n") : 1;
	(opcode.coding_byte) ? ins->coding_byte +=
	(param->type << (6 - (2 * i))) : 1;
	if (param->type == T_REG)
		ins->size++;
	else if (param->type == 3)
		ins->size += 2;
	else if (param->type == T_DIR)
	{
		if (opcode.two_bytes)
			ins->size += 2;
		else
			ins->size += 4;
	}
}

void	asm_check_param(t_ins *ins, t_op opcode)
{
	t_list	*tmp;
	t_param	*tmp_param;
	int		i;

	i = 0;
	tmp = ins->param;
	(opcode.coding_byte) ? ins->size++ : 1;
	while (tmp)
	{
		tmp_param = tmp->content;
		asm_check_param_value(ins, opcode, tmp_param, i);
		i++;
		tmp = tmp->next;
	}
	(i != opcode.nb_param) ? asm_error("Wrong argument\n") : 1;
}

void	asm_check_ins(t_asm *data)
{
	t_list	*tmp;
	t_ins	*tmp_ins;

	tmp = data->ins;
	while (tmp)
	{
		tmp_ins = tmp->content;
		if (tmp_ins->opcode)
		{
			tmp_ins->two_bytes = tmp_ins->op_code.two_bytes;
			asm_check_param(tmp_ins, tmp_ins->op_code);
		}
		tmp = tmp->next;
	}
}
