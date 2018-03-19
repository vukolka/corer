/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:45:11 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 17:45:13 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	get_flags(t_environment *env, char **param)
{
	int i;

	i = 1;
	while (param[i])
	{
		if (ft_strequ("-v", param[i]))
			env->vis_flag = 1;
		if (ft_strequ("-d", param[i]))
			env->debug_flag = 1;
		if (ft_strequ("-dump", param[i]))
		{
			if (valid_num(param[i + 1]))
				env->dump = ft_atoi(param[i + 1]);
			else
				ft_printf_last_error("incorrect dump");
			i++;
		}
		if (ft_strequ("-hl", param[i]))
			env->hide_lives = 1;
		i++;
	}
}

void	init_env(t_environment *env, int pl_count)
{
	env->cyclestodie = CYCLE_TO_DIE;
	env->nextkill = CYCLE_TO_DIE;
	env->last_check = 0;
	env->processes_queue = NULL;
	env->cycles = 0;
	env->pl_count = pl_count;
	env->fd = open("log.txt", O_RDWR | O_APPEND);
	env->debug_fd = open("debug_log.txt", O_RDWR | O_APPEND);
	env->count_proc = pl_count;
	env->vis_flag = 0;
	env->debug_flag = 0;
	env->dump = -1;
	env->players = NULL;
	env->hide_lives = 0;
}

void	init_game(char **param, t_environment *env,
					int pl_count, char **args)
{
	int			fd;
	int			ind;

	ind = 0;
	init_env(env, pl_count);
	ft_bzero(env->map, MEM_SIZE);
	ft_printf("Introducing contestants...\n");
	while (ind < pl_count)
	{
		fd = open(param[ind], O_RDONLY);
		if (fd == -1 || !get_player(fd, env, ind, pl_count))
			ft_printf_last_error("Incorrect player");
		ind++;
		close(fd);
	}
	player_num(args, pl_count, env);
	ind = 0;
	while (ind < pl_count)
	{
		process_init(env, ind, pl_count);
		ind++;
	}
}

int		main(int argc, char **param)
{
	t_environment			env;
	int						pl_count;
	char					**player_list;

	trunc_log();
	make_classes();
	pl_count = 0;
	player_list = count_players(param, argc, &pl_count);
	init_game(player_list, &env, pl_count, param);
	get_flags(&env, param);
	if (env.vis_flag)
		init_log(&env);
	vm_loop(&env);
	return (0);
}
