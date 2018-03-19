//
// Created by Maksym KONIEV on 2/18/18.
//
#include "../libft/ft_printf/ft_printf/ft_printf.h"
#include "../libft/classes_lib/linked_list.h"
#include "../libft/classes_lib/queue.h"
#include "op.h"
#include <fcntl.h>

void    trunc_log()
{
	int fd;

	fd = open("../log.txt", O_CREAT | O_TRUNC, S_IRWXU);
	close(fd);
	fd = open("../map.txt", O_CREAT | O_TRUNC, S_IRWXU);
	close(fd);
	fd = open("../debug_log.txt", O_CREAT | O_TRUNC, S_IRWXU);
	close(fd);
}

void    dump_memory(t_environment *env)
{
	int i;
	int k;

	i = 0;
	while (i < 64)
	{
		k = 0;
		ft_printf("%#4.4x :", 64 * i);
		while (k < 64)
		{
			ft_printf(" %2.2x", env->map[(64 * i) + k]);
			k++;
		}
		i++;
		ft_printf("\n");
	}
	end_game(env, 0);
}

void    sti_dop_print(t_process *proc, t_environment *env)
{
	short tmp;
	short tmp2;

	get_args(proc->command_cache, proc->program_counter, env);
	tmp = (proc->command_cache->codage[1] == 'R') ?
			(short)conv_mem(return_arg(proc, env, 1)) :
			(short)convert_arg(return_arg(proc, env, 1), proc, 1);
	tmp = (proc->command_cache->codage[1] == 'I') ?
			(short)conv_mem(return_arg(proc, env, 1)) : tmp;
	tmp2 = (proc->command_cache->codage[2] == 'R') ?
			(short)conv_mem(return_arg(proc, env, 2)) :
			(short)convert_arg(return_arg(proc, env, 2), proc, 2);
	ft_printf_fd("       | -> store to %d + %d = %d (with pc and mod %d)\n",
				env->debug_fd, tmp, tmp2, tmp + tmp2,
				(tmp + tmp2) % IDX_MOD + proc->program_counter - env->map);

}

void    print_operation(t_process *proc, t_environment *env)
{
	int i;

	i = 0;
	ft_printf_fd("P    %d | %s", env->debug_fd, proc->id, g_op_tab[proc->command_cache->op_code - 1].name);
	while (i < g_op_tab[proc->command_cache->op_code - 1].args_num)
	{
		if (proc->command_cache->codage[i] == 'N')
			break;
		if (proc->command_cache->codage[i] == 'R')
			ft_printf_fd(" r%hd", env->debug_fd, *proc->command_cache->args[i]);
		else if (proc->command_cache->codage[i] == 'D')
			ft_printf_fd(" %hd", env->debug_fd, convert_arg(proc->command_cache->args[i], proc, i));
		else if (proc->command_cache->codage[i] == 'I')
			ft_printf_fd(" %d", env->debug_fd, conv_mem(proc->command_cache->args[i]));
		i++;
	}
	if (proc->command_cache->op_code == 9)
		if (proc->carry == 1)
			ft_printf_fd(" OK", env->debug_fd);
		else
			ft_printf_fd(" FAIL", env->debug_fd);
	if (proc->command_cache->op_code == 12 || proc->command_cache->op_code == 15)
		ft_printf_fd(" (%hd)", env->debug_fd,
		             ((short)convert_arg(proc->command_cache->args[0], proc, 0) + proc->program_counter) - env->map);
	ft_printf_fd("\n", env->debug_fd);
	if (proc->command_cache->op_code == 11)
		sti_dop_print(proc, env);
}

void    print_movement(t_process *proc,
						t_environment *env, int ind, int count)
{
	int swipe;
	int i;

	i = 0;
	if (ind)
	{
		if (g_op_tab[proc->command_cache->op_code - 1].codage)
			swipe = count_swipe(proc, env);
		else if (proc->command_cache->op_code <= 16
				&& proc->command_cache->op_code > 0)
			swipe = 1 + g_op_tab[proc->command_cache->op_code - 1].lable_size;
		else
			swipe = 2;
		ft_printf_fd("ADV %d (%#.4x -> %#.4x)", env->debug_fd,
			swipe, return_ind(proc->program_counter, env) % MEM_SIZE,
			return_ind(proc->program_counter + swipe, env) % MEM_SIZE);
		while (i < swipe)
			ft_printf_fd(" %.2x", env->debug_fd,
			             *get_adr(proc->program_counter, i++, env));
	} else
		ft_printf_fd("ADV %d (%#.4x -> %#.4x)",
			env->debug_fd, count, return_ind(proc->program_counter,
			env) % MEM_SIZE, return_ind(proc->program_counter + count,
			env) % MEM_SIZE);
	ft_printf_fd("\n", env->debug_fd);
}

void    debug_log(t_process *proc, t_environment *env, int success)
{
	if (!env->debug_flag)
		return;
	if (proc->success)
		print_operation(proc, env);
	if (proc->success && proc->command_cache->op_code != 9)
		print_movement(proc, env, 1, 0);
}

void    init_log(t_environment *environment)
{
	int i;
	int fd;
	t_llist *temp;

	i = 0;
	temp = environment->players;
	fd = environment->fd;
	ft_printf_fd("<players descr>\n", fd);
	while (temp)
	{
		ft_printf_fd("[<%d> <%s> <%s>]\n", fd,
			((t_player *)(temp->content))->id,
			((t_player *)(temp->content))->name,
			((t_player *)(temp->content))->description);
		temp = temp->next;
	}
	ft_printf_fd("</players descr>\n", fd);
	fd = open("../map.txt", O_RDWR | O_APPEND);
	while (i < MEM_SIZE)
		ft_printf_fd("%c", fd, environment->map[i++]);
	log_state(environment);
}

int     return_ind(unsigned char *adr, t_environment *environment)
{
	return ((adr - environment->map) % MEM_SIZE);
}

void    log_state(t_environment *environment)
{
	int fd;
	t_llist *temp;
	t_process *head;


	temp = environment->players;
	fd = environment->fd;
	ft_printf_fd("<players>\n", fd);
	while (temp)
	{
		ft_printf_fd("[<%d> <%d> <%d>]\n", fd,
			((t_player *)(temp->content))->id,
			((t_player *)(temp->content))->current_lives,
			((t_player *)(temp->content))->last_live_cycle);
		temp = temp->next;
	}
	ft_printf_fd("</players>\n<processes>\n", fd);
	head = environment->processes_queue;
	while (environment->processes_queue)
	{
		ft_printf_fd("[<%d> <%d> <%d>]\n", fd,
			environment->processes_queue->player_id,
			environment->processes_queue->program_counter - environment->map,
			environment->processes_queue->live_executions);
		environment->processes_queue = environment->processes_queue->next;
	}
	environment->processes_queue = head;
	ft_printf_fd("</processes>\n", fd);
}

void    log_event(t_process *process, unsigned char *destination_adr,
					t_environment *environment, int n)
{
	int fd;
	int i;

	i = 0;
	fd = environment->fd;
	if (!environment->vis_flag)
		return ;
	ft_printf_fd("[<%d> <%d> ", fd,
	             process->player_id,
	             return_ind(destination_adr, environment));
	while (i < n)
	{
		ft_printf_fd("<%d> ", fd, *(destination_adr + i));
		i++;
	}
	ft_printf_fd("]\n", fd);
}