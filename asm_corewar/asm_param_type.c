/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_param_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:35:31 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 16:35:32 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_get_num_param(t_param *p, char *str)
{
	(*str == '%') ? str++ : NULL;
	p->value = ft_atoi(str);
	(*str == '-') ? str++ : NULL;
	while (ft_isdigit(*str))
		str++;
	(*str) ? asm_error("Wrong parameter\n") : 1;
	(!(p->type & T_DIR)) ? p->type = 3 : 1;
	p->label = NULL;
}

void	asm_get_reg_param(t_param *p, char *str)
{
	str++;
	p->type += T_REG;
	p->value = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	(*str) ? asm_error("Wrong parameter\n") : 1;
	(p->value > 16 || p->value == 0) ?
	asm_error("reg must be from 1 to 16\n") : 1;
	p->label = NULL;
}

void	asm_get_label_param(t_param *p, char *str)
{
	int		i;

	i = 0;
	(*str == '%') ? str++ : NULL;
	str++;
	while (str[i] && asm_valid_label_char(str[i], LABEL_CHARS))
		i++;
	(str[i]) ? asm_error("Wrong label parameter\n") : 1;
	(!(p->type & T_DIR)) ? p->type = 3 : 1;
	p->label = ft_strdup(str);
}
