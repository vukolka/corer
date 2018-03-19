/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:33:53 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:33:54 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_ins			*asm_init_ins(void)
{
	t_ins	*new_ins;

	new_ins = (t_ins *)malloc(sizeof(t_ins));
	new_ins->opcode = 0;
	new_ins->param = NULL;
	new_ins->coding_byte = 0;
	new_ins->size = 1;
	new_ins->label = NULL;
	return (new_ins);
}

void			asm_data_init(t_asm *data)
{
	data->header = (t_header *)malloc(sizeof(t_header));
	data->header->magic = COREWAR_EXEC_MAGIC;
	data->ins = NULL;
}
