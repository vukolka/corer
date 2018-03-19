/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:18:37 by mkoniev           #+#    #+#             */
/*   Updated: 2018/03/19 18:18:38 by mkoniev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_OP_H
# include <fcntl.h>
# include <zconf.h>
# include "libft.h"
# include "ft_printf.h"
# include "../libft/classes_lib/classes_lib.h"
# include "../libft/classes_lib/linked_list.h"
# include "../libft/classes_lib/queue.h"
# include "../libft/classes_lib/new.h"
# define COREWAR_OP_H
# define IND_SIZE					2
# define REG_SIZE					4
# define DIR_SIZE					REG_SIZE
# define REG_CODE					1
# define DIR_CODE					2
# define IND_CODE					3
# define MAX_ARGS_NUMBER				4
# define MAX_PLAYERS					4
# define MEM_SIZE					(4096)
# define IDX_MOD						(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE				(MEM_SIZE / 6)
# define COMMENT_CHAR				'#'
# define LABEL_CHAR					':'
# define DIRECT_CHAR					'%'
# define SEPARATOR_CHAR				','
# define LABEL_CHARS					"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING				".name"
# define COMMENT_CMD_STRING			".comment"
# define REG_NUMBER					16
# define CYCLE_TO_DIE				1536
# define CYCLE_DELTA					50
# define NBR_LIVE					21
# define MAX_CHECKS					10

typedef char	t_arg_type;
# define T_REG						1
# define T_DIR						2
# define T_IND						4
# define T_LAB						8
# define PROG_NAME_LENGTH			(128)
# define COMMENT_LENGTH				(2048)
# define COREWAR_EXEC_MAGIC			0xea83f3

typedef struct			s_command_cache
{
	int					cycles_left;
	unsigned char		op_code;
	unsigned char		**args;
	char				*codage;
}						t_command_cache;

typedef struct			s_process
{
	unsigned int		player_id;
	int					id;
	unsigned char		memory[REG_NUMBER * REG_SIZE];
	unsigned char		*program_counter;
	int					carry;
	int					new;
	unsigned int		live_executions;
	t_command_cache		*command_cache;
	int					success;
	struct s_process	*next;
}						t_process;
typedef struct			s_environment
{
	t_process			*processes_queue;
	void				*players;
	int					pl_count;
	int					cyclestodie;
	int					nextkill;
	unsigned char		map[MEM_SIZE];
	int					last_check;
	int					fd;
	int					debug_fd;
	unsigned long int	cycles;
	int					count_proc;
	int					debug_flag;
	int					vis_flag;
	int					dump;
	int					hide_lives;
}						t_environment;
typedef struct			s_op
{
	char				*name;
	char				args_num;
	char				arg[3];
	char				opcode;
	int					cycles;
	int					codage;
	int					carry;
	int					lable_size;
	void				(*func)(t_process *, t_environment *);
	int					(*valid)(t_process *, t_environment *);
	unsigned char		max_swipe;
}						t_op;
typedef struct s_player	t_player;
struct					s_player
{
	unsigned char		*name;
	unsigned char		*description;
	int					size;
	unsigned int		id;
	unsigned long int	last_live_cycle;
	long				current_lives;
};
void					ft_printf_last_error(char *err);
void					init_game(char **param, t_environment *env,
							int pl_count, char **args);
int						get_player(int fd, t_environment *env,
							int i, int pl_count);
void					process_init(t_environment *env, int i, int pl_count);
unsigned const char		*hex_convert_pair_to_alph(unsigned char const *tmp);
void					log_state(t_environment *environment);
void					log_event(t_process *process, unsigned char
						*destination_adr, t_environment *environment, int n);
void					trunc_log();
void					init_log(t_environment *environment);
char					**count_players(char **str, int num, int *pl_count);
void					test(char *str);
unsigned char			*get_adr(unsigned char *adr, int ind,
							t_environment *env);
void					set_delay(t_process *current_proc);
void					ft_fork(t_process *process, t_environment *env);
void					live(t_process *process, t_environment *env);
int						valid_live(t_process *process, t_environment *env);
void					just_skip(t_process *process, t_environment *env);
int						stand_valid(t_process *process, t_environment *env);
void					ft_lfork(t_process *process, t_environment *env);
void					get_args(t_command_cache *p_cache,
							unsigned char *counter, t_environment *env);
char					*decode_codage(t_command_cache *p_cache, unsigned char
							*counter, t_environment *env);
void					ft_ld (t_process *process, t_environment *env);
int						valid_ld(t_process *process, t_environment *env);
void					ft_st(t_process *process, t_environment *env);
int						valid_st(t_process *process, t_environment *env);
void					ft_sub(t_process *process, t_environment *env);
void					ft_add(t_process *process, t_environment *env);
void					ft_zjmp(t_process *process, t_environment *env);
int						valid_aff(t_process *process, t_environment *env);
void					ft_aff(t_process *process, t_environment *env);
void					n_cpy_reg(t_process *process, unsigned char *src,
							unsigned char *start, int count);
void					n_cpy_map(t_environment *env, unsigned char *src,
							int start, int count);
void					ft_and(t_process *process, t_environment *env);
int						add_valid(t_process *process, t_environment *env);
void					ft_or(t_process *process, t_environment *env);
void					ft_xor(t_process *process, t_environment *env);
int						valid_and(t_process *process, t_environment *env);
void					ft_sti(t_process *process, t_environment *env);
int						sti_valid(t_process *process, t_environment *env);
int						fork_valid(t_process *process, t_environment *env);
void					ft_ldi(t_process *process, t_environment *env);
int						ldi_valid(t_process *process, t_environment *env);
void					ft_lld (t_process *process, t_environment *env);
void					ft_lldi(t_process *process, t_environment *env);
unsigned char			*deconvert_arg(int num);
int						return_ind(unsigned char *adr, t_environment
							*environment);
int						return_spos(t_process *process, t_environment *env);
int						check_val_regs(t_process *process, t_environment *env);
void					debug_log(t_process *proc, t_environment *env,
							int success);
void					stand_debug(t_process *proc, t_environment *env);
void					debug_sti(t_process *proc, t_environment *env);
int						conv_mem(unsigned char *arg);
unsigned char			*return_arg(t_process *proc, t_environment *env,
							int ind);
int						convert_arg(unsigned char *arg, t_process *proc,
							int num);
void					debug_sti(t_process *proc, t_environment *env);
int						count_swipe(t_process *proc, t_environment *env);
void					print_movement(t_process *proc, t_environment *env,
							int ind, int count);
void					*dequeue_end(void *s_self);
t_process				*get_from_head(t_process **list);
void					add_to_head(t_process *new, t_process **list);
void					add_to_tail(t_process *new, t_process **list);
void					end_game(t_environment *env, int end);
void					dump_memory(t_environment *env);
void					malloc_cache(t_process *new);
void					vm_loop(t_environment *environment);
void					make_turn(t_environment *environment);
void					process_operation(t_process *current_proc,
							t_environment *env);
void					print_operation(t_process *proc, t_environment *env);
void					while_in_logstate(t_environment *environment);
int						valid_num(char *num);
void					player_num(char **flags,
								int pl_count, t_environment *env);
int						set_zero(t_environment *env);
void					delete_proc(t_process **proc);
void					put_player_ints(t_player *player, int i);
int						add_to_map(int fd, t_environment *env,
									int ind, int pl_count);
int						get_player(int fd, t_environment *env,
							int i, int pl_count);
void					get_name_and_desc(int fd, t_player *player);
static t_op				g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, 0, 0, 4, live, valid_live, 5},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 0, 4, ft_ld, valid_ld, 7},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 0, 4, ft_st, valid_st, 5},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 0, 4, ft_add, add_valid, 5},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 0, 4, ft_sub, add_valid, 5},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, 1, 0, 4, ft_and, valid_and, 11},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, 1, 0, 4, ft_or, valid_and, 11},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, 1, 0, 4, ft_xor, valid_and, 11},
	{"zjmp", 1, {T_DIR}, 9, 20, 0, 1, 2, ft_zjmp, fork_valid, 5},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10,
		25, 1, 1, 2, ft_ldi, ldi_valid, 7},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11,
		25, 1, 1, 2, ft_sti, sti_valid, 7},
	{"fork", 1, {T_DIR}, 12, 800, 0, 1, 2, ft_fork, fork_valid, 3},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 0, 4, ft_lld, valid_ld, 7},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14,
		50, 1, 1, 2, ft_lldi, ldi_valid, 7},
	{"lfork", 1, {T_DIR}, 15, 1000, 0, 1, 2, ft_lfork, fork_valid, 3},
	{"aff", 1, {T_REG}, 16, 2, 1, 0, 4, ft_aff, valid_aff, 3},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0, 0, 0}
};
#endif
