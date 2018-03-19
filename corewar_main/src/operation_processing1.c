/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_processing1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:04:50 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:04:50 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int				add_valid(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (ft_strequ("RRR", process->command_cache->codage)
		&& check_val_regs(process, env))
		return (1);
	return (0);
}

void			ft_add(t_process *process, t_environment *env)
{
	int				temp;
	unsigned char	*dec;

	temp = conv_mem(return_arg(process, env, 0))
		+ conv_mem(return_arg(process, env, 1));
	dec = deconvert_arg(temp);
	n_cpy_reg(process, dec, return_arg(process, env, 2), 4);
	process->carry = (temp) ? 0 : 1;
	process->program_counter = get_adr(process->program_counter, 5, env);
	process->success = 1;
	free(dec);
	set_delay(process);
}

int				valid_live(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	return (1);
}

void			live(t_process *process, t_environment *env)
{
	t_llist *temp;

	temp = env->players;
	process->live_executions += 1;
	while (temp && ((t_player *)(temp->content))->id !=
				(unsigned)-convert_arg(process->command_cache->args[0],
					process, 0))
		temp = temp->next;
	if (temp && ((t_player *)(temp->content))->current_lives != -1)
	{
		((t_player *)(temp->content))->current_lives += 1;
		((t_player *)(temp->content))->last_live_cycle = env->cycles;
		if (!env->hide_lives)
			ft_printf("A process shows that player %s is alive\n",
					((t_player *)(temp->content))->name);
	}
	process->program_counter = get_adr(process->program_counter, 5, env);
	process->success = 1;
	set_delay(process);
}

void			set_delay(t_process *current_proc)
{
	current_proc->command_cache->op_code = *current_proc->program_counter;
	ft_bzero(current_proc->command_cache->args[0], 4);
	ft_bzero(current_proc->command_cache->args[1], 4);
	ft_bzero(current_proc->command_cache->args[2], 4);
	if (current_proc->command_cache->codage)
		ft_memdel((void **)&(current_proc->command_cache->codage));
	if (current_proc->command_cache->op_code <= 16
		&& current_proc->command_cache->op_code > 0)
	{
		current_proc->command_cache->cycles_left =
				g_op_tab[current_proc->command_cache->op_code - 1].cycles - 1;
	}
	else
		current_proc->command_cache->cycles_left = 0;
}
