/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_instructions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:38:26 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:38:27 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			asm_push_ins(t_asm *data, t_ins *new_ins)
{
	if (new_ins->opcode)
	{
		(data->ins == NULL) ? data->ins = ft_lstnew(new_ins, sizeof(t_ins)) :
		ft_lstappend(&(data->ins), ft_lstnew(new_ins, sizeof(t_ins)));
		(new_ins) ? free(new_ins) : 1;
		new_ins = asm_init_ins();
	}
}

void			asm_parse_instruction(t_asm *data, int fd)
{
	t_ins	*new_ins;
	char	*line;
	int		ret;

	new_ins = asm_init_ins();
	while ((ret = get_next_line(fd, &line)))
	{
		if (asm_is_com(line))
			continue ;
		asm_get_ins_line(new_ins, line, g_op_tab);
		asm_push_ins(data, new_ins);
	}
	(ret == -1) ? asm_error("gnl -1\n") : 1;
	if (new_ins->label)
	{
		new_ins->size = 0;
		(data->ins == NULL) ? data->ins = ft_lstnew(new_ins, sizeof(t_ins)) :
			ft_lstappend(&(data->ins), ft_lstnew(new_ins, sizeof(t_ins)));
	}
}
