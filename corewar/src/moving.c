#include <ft_printf.h>
#include "op.h"
#include "../libft/classes_lib/new.h"
#include "../libft/classes_lib/queue.h"
#include "../libft/classes_lib/linked_list.h"
#include "../libft/ft_printf/libftprintf/libft.h"

void			add_to_tail(t_process *new, t_process **list)
{
	t_process *head;

	head = *list;
	if (!*list)
	{
		*list = new;
		return ;
	}
	while ((*list)->next)
		(*list) = (*list)->next;
	new->next = NULL;
	(*list)->next = new;
	*list = head;
}

void			add_to_head(t_process *new, t_process **list)
{
	new->next = *list;
	*list = new;
}

t_process		*get_from_head(t_process **list)
{
	t_process *temp;

	temp = *list;
	*list = (*list)->next;
	temp->next = NULL;
	return (temp);
}

unsigned char	*get_adr(unsigned char *adr, int ind, t_environment *env)
{
	int moved;
	int delta;

	moved = 0;
	ind = ind % MEM_SIZE;
	delta = (ind >= 0) ? 1 : -1;
	while (moved != ind)
	{
		if (adr + delta - env->map < MEM_SIZE && adr + delta - env->map >= 0)
			adr += delta;
		else
			adr += (delta > 0) ? (-MEM_SIZE + 1) : (MEM_SIZE - 1);
		moved += delta;
	}
	return (adr);
}

char			*decode_codage(t_command_cache *p_cache,
						unsigned char *counter, t_environment *env)
{
	char			*ret;
	unsigned char	codage;
	char			*a;

	codage = *get_adr(counter, 1, env);
	a = "NRDI";
	ret = ft_memalloc(4 * sizeof(char));
	if (g_op_tab[p_cache->op_code - 1].codage)
	{
		ret[0] = a[codage >> 6];
		ret[1] = a[(codage & 0b00110000) >> 4];
		ret[2] = a[(codage & 0b00001100) >> 2];
	}
	else
		ret = ft_strdup("DNN");
	return (ret);
}

void			get_args(t_command_cache *p_cache,
						unsigned char *counter, t_environment *env)
{
	int		i;
	size_t	k;
	int		a;

	i = 1;
	if (g_op_tab[p_cache->op_code - 1].codage)
		counter = get_adr(counter, 2, env);
	else
		counter = get_adr(counter, 1, env);
	while (i <= g_op_tab[p_cache->op_code - 1].args_num)
	{
		k = 0;
		a = 0;
		if (p_cache->codage[i - 1] == 'I')
			k += 2;
		else if (p_cache->codage[i - 1] == 'D'
				|| !g_op_tab[p_cache->op_code - 1].codage)
			k += g_op_tab[p_cache->op_code - 1].lable_size;
		else if (p_cache->codage[i - 1] == 'R')
			k++;
		while (a < k)
		{
			p_cache->args[i - 1][a] = *(counter + a);
			a++;
		}
		counter = get_adr(counter, k, env);
		i++;
	}
}

void			make_move(t_process *curr_process, t_environment *env)
{
	t_command_cache *cache;

	cache = curr_process->command_cache;
	if (cache->cycles_left > 0)
	{
		cache->cycles_left--;
		return ;
	}
	else if (cache->cycles_left == 0)
	{
		if (g_op_tab[(curr_process->command_cache->op_code) - 1].codage)
			curr_process->command_cache->codage =
					decode_codage(curr_process->command_cache,
						curr_process->program_counter, env);
		else
			curr_process->command_cache->codage = ft_strdup("DNN");
		process_operation(curr_process, env);
		return ;
	}
	if (cache->op_code == 0)
	{
		just_skip(curr_process, env);
		return ;
	}
}

void			make_turn(t_environment *environment)
{
	t_process		*temp_queue;
	t_process		*current_process;
	int				fd;

	environment->cycles += 1;
	fd = environment->fd;
	temp_queue = NULL;
	if (environment->vis_flag)
		ft_printf_fd("<cycle>\n[<%d> <%d>]\n</cycle>\n<events>\n", fd,
	environment->cycles, environment->cyclestodie);
	while (environment->processes_queue)
	{
		current_process = get_from_head(&(environment->processes_queue));
		if (!current_process->new)
		{
			make_move(current_process, environment);
			add_to_tail(current_process, &temp_queue);
		}
		else
			add_to_head(current_process, &temp_queue);
		current_process->new = 0;
	}
	fd = environment->fd;
	if (environment->vis_flag)
		ft_printf_fd("</events>\n", fd);
	free(environment->processes_queue);
	environment->processes_queue = temp_queue;
}
