/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:30:24 by mvukolov          #+#    #+#             */
/*   Updated: 2018/03/19 15:33:23 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "minilib/minilib.h"

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE				(4*1024)

# define IDX_MOD				(MEM_SIZE / 8)

# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define MASK1 0xFF000000
# define MASK2 0x00FF0000
# define MASK3 0x0000FF00
# define MASK4 0x000000FF

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef	struct		s_op
{
	char			*name;
	int				nb_param;
	int				param[3];
	char			opcode;
	int				cycle;
	char			*full_name;
	int				coding_byte;
	int				two_bytes;
}					t_op;

typedef	struct		s_param
{
	unsigned int	value;
	char			*label;
	int				type;
}					t_param;

typedef struct		s_ins
{
	t_list			*label;
	char			opcode;
	char			coding_byte;
	t_op			op_code;
	bool			two_bytes;
	t_list			*param;
	unsigned int	size;
}					t_ins;

typedef struct		s_asm
{
	t_header		*header;
	t_list			*ins;
	t_list			*label_adress;
}					t_asm;

static t_op			g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

void				asm_error(char *message);
void				asm_check_ins(t_asm *data);
void				asm_check_param(t_ins *ins, t_op opcode);
void				asm_get_ins_line(t_ins *new_ins,
						char *line, t_op t_op_tab[17]);
void				asm_get_ins_param(t_ins	*ins, char **tab);
void				asm_get_label_param(t_param *p, char *str);
void				asm_get_reg_param(t_param *p, char *str);
void				asm_get_num_param(t_param *p, char *str);
void				asm_print_bytecode(t_asm *data, char *name);
void				asm_print_ins(t_asm *data, int fd);
void				asm_print_uint_hex(int fd, unsigned int nb, char l);
void				asm_get_prog_size(t_asm *data);
void				asm_data_init(t_asm *data);
void				asm_parse_header(t_asm *data, int fd);
void				asm_parse_instruction(t_asm *data, int fd);
bool				asm_get_opcode(t_ins *new_ins, char *str, t_op op);
bool				asm_valid_label_char(char c, char *label_chars);
bool				asm_is_com(char *str);
bool				asm_blank(char *str);
char				**asm_split_line(char *line);
t_ins				*asm_init_ins(void);

#endif
