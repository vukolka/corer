#include <printf.h>
#include <libft.h>
#include <ft_printf/ft_printf.h>
#include "op.h"
#include "../libft/classes_lib/linked_list.h"
#include "../libft/classes_lib/queue.h"

int				count_swipe(t_process *proc, t_environment *env)
{
	int swipe;
	int i;

	i = 0;
	swipe = (g_op_tab[proc->command_cache->op_code - 1].codage) ? 2 : 1;
	while (i < g_op_tab[proc->command_cache->op_code - 1].args_num)
	{
		if (proc->command_cache->codage[i] == 'D')
			swipe += g_op_tab[*proc->program_counter - 1].lable_size;
		else if (proc->command_cache->codage[i] == 'I')
			swipe += 2;
		else if (proc->command_cache->codage[i] == 'R')
			swipe += 1;
		i++;
	}
	return (swipe);
}

int				convert_arg(unsigned char *arg, t_process *proc, int num)
{
	int				res;
	unsigned int	temp;

	temp = arg[0];
	res = temp << 24;
	temp = arg[1];
	res = res | (temp << 16);
	temp = arg[2];
	res = res | (temp << 8);
	temp = arg[3];
	res = res | (temp);
	if (proc->command_cache->codage[num] == 'D')
		res = res >> ((4 -
			g_op_tab[proc->command_cache->op_code - 1].lable_size) * 8);
	else if (proc->command_cache->codage[num] == 'I')
	{
		res = res >> 16;
		return ((res));
	}
	else
		res = res >> 24;
	return (res);
}

int				conv_mem(unsigned char *arg)
{
	int				res;
	unsigned int	temp;

	temp = arg[0];
	res = temp << 24;
	temp = arg[1];
	res = res | (temp << 16);
	temp = arg[2];
	res = res | (temp << 8);
	temp = arg[3];
	res = res | (temp);
	return (res);
}

unsigned char	*return_arg(t_process *proc, t_environment *env, int ind)
{
	if (proc->command_cache->codage[ind] == 'D')
		return (proc->command_cache->args[ind]);
	else if (proc->command_cache->codage[ind] == 'R')
		return (&proc->memory[convert_arg(proc->command_cache->args[ind],
			proc, ind) * (REG_SIZE) - 4]);
	else if (proc->command_cache->codage[ind] == 'I'
			&& (proc->command_cache->op_code != 3))
		return (get_adr(proc->program_counter,
				convert_arg(proc->command_cache->args[ind], proc, ind), env));
	else if (proc->command_cache->codage[ind] == 'I')
		return (proc->command_cache->args[ind]);
	return (0);
}

void			process_operation(t_process *current_proc, t_environment *env)
{
	if (current_proc->command_cache->op_code <= 16 &&
		current_proc->command_cache->op_code > 0
		&& g_op_tab[current_proc->command_cache->op_code - 1].valid(current_proc,
		env))
	{
		current_proc->success = 1;
		debug_log(current_proc, env, 1);
		g_op_tab[current_proc->command_cache->op_code - 1].func(current_proc,
			env);
	}
	else
	{
		current_proc->success = 0;
		debug_log(current_proc, env, 0);
		just_skip(current_proc, env);
	}
}

void			just_skip(t_process *process, t_environment *env)
{
	process->success = 0;
	if (*process->program_counter == 0 || *process->program_counter > 16)
	{
		process->program_counter = get_adr(process->program_counter, 1, env);
		set_delay(process);
		return ;
	}
	if (env->debug_flag)
		print_movement(process, env, 0, count_swipe(process, env));
	process->program_counter = get_adr(process->program_counter,
		count_swipe(process, env), env);
	set_delay(process);
}

int				check_val_regs(t_process *process, t_environment *env)
{
	int		i;
	char	tmp;

	i = 0;
	while (i < 3)
	{
		tmp = *process->command_cache->args[i];
		if (process->command_cache->codage[i] == 'R' &&
			(tmp <= 0 || tmp > 16))
			return (0);
		i++;
	}
	return (1);
}

int				ldi_valid(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (!ft_strchr(process->command_cache->codage, 'N')
		&& process->command_cache->codage[2] == 'R'
		&& process->command_cache->codage[1] != 'I'
		&& check_val_regs(process, env))
		return (1);
	return (0);
}

void			ft_ldi(t_process *process, t_environment *env)
{
	int	counter_swipe;
	int tmp;
	int tmp2;

	counter_swipe = count_swipe(process, env);
	tmp = (process->command_cache->codage[0] == 'R') ?
		conv_mem(return_arg(process, env, 0)) :
		convert_arg(return_arg(process, env, 0), process, 0);
	tmp = (process->command_cache->codage[0] == 'I') ?
		conv_mem(return_arg(process, env, 0)) : tmp;
	tmp2 = (process->command_cache->codage[1] == 'R') ?
		conv_mem(return_arg(process, env, 1)) :
		convert_arg(return_arg(process, env, 1), process, 1);
	n_cpy_reg(process, get_adr(process->program_counter,
		((tmp + tmp2) % IDX_MOD), env), return_arg(process, env, 2), 4);
	process->program_counter = get_adr(process->program_counter,
		counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

void			ft_lldi(t_process *process, t_environment *env)
{
	int	counter_swipe;
	int tmp;
	int tmp2;

	counter_swipe = count_swipe(process, env);
	tmp = (process->command_cache->codage[0] == 'R') ?
		conv_mem(return_arg(process, env, 0)) :
		convert_arg(return_arg(process, env, 0), process, 0);
	tmp = (process->command_cache->codage[0] == 'I') ?
		conv_mem(return_arg(process, env, 0)) : tmp;
	tmp2 = (process->command_cache->codage[1] == 'R') ?
		conv_mem(return_arg(process, env, 1)) :
		convert_arg(return_arg(process, env, 1), process, 1);
	n_cpy_reg(process, get_adr(process->program_counter,
		(tmp + tmp2), env), return_arg(process, env, 2), 4);
	process->carry = conv_mem(return_arg(process, env, 2)) ? 0 : 1;
	process->program_counter = get_adr(process->program_counter,
		counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

int				sti_valid(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (!ft_strchr(process->command_cache->codage, 'N')
		&& process->command_cache->codage[0] == 'R'
		&& process->command_cache->codage[2] != 'I'
		&& check_val_regs(process, env))
		return (1);
	return (0);
}

void			ft_sti(t_process *process, t_environment *env)
{
	int	counter_swipe;
	int	tmp;
	int	tmp2;

	counter_swipe = count_swipe(process, env);
	tmp = (process->command_cache->codage[1] == 'R') ?
		conv_mem(return_arg(process, env, 1)) :
		convert_arg(return_arg(process, env, 1), process, 1);
	tmp = (process->command_cache->codage[1] == 'I') ?
		conv_mem(return_arg(process, env, 1)) : tmp;
	tmp2 = (process->command_cache->codage[2] == 'R') ?
		conv_mem(return_arg(process, env, 2)) :
		convert_arg(return_arg(process, env, 2), process, 2);
	n_cpy_map(env, return_arg(process, env, 0),
		return_ind(get_adr(process->program_counter,
			(tmp + tmp2) % IDX_MOD, env), env), 4);
	log_event(process, get_adr(env->map,
		return_ind(get_adr(process->program_counter,
			(tmp + tmp2) % IDX_MOD, env), env), env), env, 4);
	process->program_counter = get_adr(process->program_counter,
		counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

int				fork_valid(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	return (1);
}

void			malloc_cache(t_process *new)
{
	new->command_cache =
		(t_command_cache *)ft_memalloc(sizeof(t_command_cache));
	new->command_cache->args =
		(unsigned char **)ft_memalloc(sizeof(unsigned char *) * 3);
	new->command_cache->args[0] =
		(unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
	new->command_cache->args[1] =
		(unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
	new->command_cache->args[2] =
		(unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
}

void			ft_fork(t_process *process, t_environment *env)
{
	t_process	*new;
	int			tmp;

	new = (t_process *)ft_memalloc(sizeof(t_process));
	new->player_id = process->player_id;
	new->carry = process->carry;
	new->live_executions = process->live_executions;
	n_cpy_reg(new, &(process->memory[0]), &(new->memory[0]), 64);
	tmp = convert_arg(return_arg(process, env, 0), process, 0);
	new->program_counter = get_adr(process->program_counter,
		tmp % IDX_MOD, env);
	malloc_cache(new);
	new->id = ++env->count_proc;
	process->program_counter = get_adr(process->program_counter, 3, env);
	new->new = 1;
	set_delay(process);
	set_delay(new);
	add_to_head(new, &env->processes_queue);
}

void			ft_zjmp(t_process *process, t_environment *env)
{
	int tmp;

	if (process->carry)
	{
		tmp = convert_arg(return_arg(process, env, 0), process, 0);
		process->program_counter =
			get_adr(process->program_counter, tmp % IDX_MOD, env);
		process->success = 1;
	}
	else
	{
		process->program_counter = get_adr(process->program_counter, 3, env);
		process->success = 0;
	}
	set_delay(process);
}

void			ft_lfork(t_process *process, t_environment *env)
{
	t_process	*new;
	int			tmp;

	new = (t_process *)ft_memalloc(sizeof(t_process));
	new->player_id = process->player_id;
	new->carry = process->carry;
	new->live_executions = process->live_executions;
	n_cpy_reg(new, &(process->memory[0]), &(new->memory[0]), 64);
	tmp = convert_arg(return_arg(process, env, 0), process, 0);
	new->program_counter = get_adr(process->program_counter, tmp, env);
	malloc_cache(new);
	new->id = ++env->count_proc;
	process->program_counter = get_adr(process->program_counter, 3, env);
	process->success = 1;
	new->new = 1;
	set_delay(process);
	set_delay(new);
	add_to_head(new, &env->processes_queue);
}

void			n_cpy_map(t_environment *env, unsigned char *src,
				int start, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		*get_adr(env->map, (i + start), env) = src[i];
		i++;
	}
}

void			n_cpy_reg(t_process *process, unsigned char *src,
				unsigned char *start, int count)
{
	int i;

	i = 0;
	while (i < count && start != process->memory + (REG_SIZE * REG_NUMBER))
	{
		start[i] = src[i];
		i++;
	}
}

int				valid_aff(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (process->command_cache->codage[0] == 'R' &&
		check_val_regs(process, env))
		return (1);
	return (0);
}

void			ft_aff(t_process *process, t_environment *env)
{
	int i;

	i = 0;
	while (i < REG_SIZE)
	{
		ft_printf("%c", return_arg(process, env, 0)[i] % 128);
		i++;
	}
	ft_printf("\n");
	process->program_counter = get_adr(process->program_counter, 3, env);
	process->success = 1;
	set_delay(process);
}

int				valid_ld(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (process->command_cache->codage[1] == 'R' &&
		(process->command_cache->codage[0] == 'I' ||
			process->command_cache->codage[0] == 'D')
			&& process->command_cache->codage[2] == 'N'
				&& check_val_regs(process, env))
		return (1);
	return (0);
}

void			ft_ld(t_process *process, t_environment *env)
{
	int	counter_swipe;

	counter_swipe = count_swipe(process, env);
	if (process->command_cache->codage[0] == 'D')
		n_cpy_reg(process, return_arg(process, env, 0),
			return_arg(process, env, 1), 4);
	else if (process->command_cache->codage[0] == 'I')
		n_cpy_reg(process,
			deconvert_arg(conv_mem(return_arg(process, env, 0))
			% IDX_MOD), return_arg(process, env, 1), 4);
	process->carry = conv_mem(return_arg(process, env, 1)) ? 0 : 1;
	process->program_counter =
		get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

void			ft_lld(t_process *process, t_environment *env)
{
	int	counter_swipe;

	counter_swipe = count_swipe(process, env);
	if (process->command_cache->codage[0] == 'D')
		n_cpy_reg(process, return_arg(process, env, 0),
			return_arg(process, env, 1), 4);
	else if (process->command_cache->codage[0] == 'I')
		n_cpy_reg(process, return_arg(process, env, 0),
			return_arg(process, env, 1), 4);
	process->carry = conv_mem(return_arg(process, env, 1)) ? 0 : 1;
	process->program_counter =
		get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

int				valid_st(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (process->command_cache->codage[0] == 'R' &&
		(process->command_cache->codage[1] == 'I'
		|| process->command_cache->codage[1] == 'R')
		&& check_val_regs(process, env))
		return (1);
	return (0);
}

void			ft_st(t_process *process, t_environment *env)
{
	int	counter_swipe;

	counter_swipe = count_swipe(process, env);
	if (process->command_cache->codage[1] == 'I')
	{
		n_cpy_map(env, return_arg(process, env, 0),
			return_ind(get_adr(process->program_counter,
	conv_mem(return_arg(process, env, 1))
			% IDX_MOD, env), env), 4);
		log_event(process, get_adr(process->program_counter,
	conv_mem(return_arg(process, env, 1))
			% IDX_MOD, env), env, 4);
	}
	else if (process->command_cache->codage[1] == 'R')
		n_cpy_reg(process, return_arg(process, env, 0),
			return_arg(process, env, 1), 4);
	process->program_counter =
		get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

int				valid_and(t_process *process, t_environment *env)
{
	get_args(process->command_cache, process->program_counter, env);
	if (!ft_strchr(process->command_cache->codage, 'N')
		&& process->command_cache->codage[2] == 'R'
		&& check_val_regs(process, env))
		return (1);
	return (0);
}

void			ft_and(t_process *process, t_environment *env)
{
	int				counter_swipe;
	int				i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	counter_swipe = count_swipe(process, env);
	while (i < 4)
	{
		tmp1 = return_arg(process, env, 0);
		tmp2 = return_arg(process, env, 1);
		return_arg(process, env, 2)[i] = tmp1[i] & tmp2[i];
		i++;
	}
	process->carry = conv_mem(return_arg(process, env, 2)) ? 0 : 1;
	process->program_counter =
		get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

void			ft_or(t_process *process, t_environment *env)
{
	int				counter_swipe;
	int				i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	counter_swipe = count_swipe(process, env);
	while (i < 4)
	{
		tmp1 = return_arg(process, env, 0);
		tmp2 = return_arg(process, env, 1);
		return_arg(process, env, 2)[i] = tmp1[i] | tmp2[i];
		i++;
	}
	process->carry = conv_mem(return_arg(process, env, 2)) ? 0 : 1;
	process->program_counter =
		get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

void			ft_xor(t_process *process, t_environment *env)
{
	int				counter_swipe;
	int				i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	counter_swipe = count_swipe(process, env);
	i = 0;
	while (i < 4)
	{
		tmp1 = return_arg(process, env, 0);
		tmp2 = return_arg(process, env, 1);
		return_arg(process, env, 2)[i] = tmp1[i] ^ tmp2[i];
		i++;
	}
	process->carry = conv_mem(return_arg(process, env, 2)) ? 0 : 1;
	process->program_counter =
		get_adr(process->program_counter, counter_swipe, env);
	process->success = 1;
	set_delay(process);
}

unsigned char	*deconvert_arg(int num)
{
	unsigned char	*res;
	int				temp;

	res = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
	temp = num;
	res[0] = (unsigned char)(temp >> 24);
	temp = num;
	res[1] = (unsigned char)(((temp << 8) >> 24));
	temp = num;
	res[2] = (unsigned char)(((temp << 16) >> 24));
	temp = num;
	res[3] = (unsigned char)(((temp << 24) >> 24));
	return (res);
}

void			ft_sub(t_process *process, t_environment *env)
{
	int				temp;
	unsigned char	*dec;

	temp = conv_mem(return_arg(process, env, 0))
			- conv_mem(return_arg(process, env, 1));
	dec = deconvert_arg(temp);
	n_cpy_reg(process, dec, return_arg(process, env, 2), 4);
	process->carry = (temp) ? 0 : 1;
	process->program_counter = get_adr(process->program_counter, 5, env);
	process->success = 1;
	free(dec);
	set_delay(process);
}

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
			-convert_arg(process->command_cache->args[0], process, 0))
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
		ft_memdel(&(current_proc->command_cache->codage));
	if (current_proc->command_cache->op_code <= 16
		&& current_proc->command_cache->op_code > 0)
	{
		current_proc->command_cache->cycles_left =
		g_op_tab[current_proc->command_cache->op_code - 1].cycles - 1;
	}
	else
		current_proc->command_cache->cycles_left = 0;
}
