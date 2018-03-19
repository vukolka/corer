NAME = minilib.a
CFL = -Wall -Werror -Wextra -c -O3 
FILES = ft_atoi.c ft_isdigit.c ft_lstadd.c ft_lstnew.c ft_memalloc.c\
		ft_memcpy.c ft_putchar.c ft_memset.c ft_putstr.c ft_putstr_fd.c \
		ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c\
		ft_strjoin.c ft_strlen.c ft_strncat.c ft_strsplit.c ft_strnew.c\
		ft_strstr.c ft_tablen.c get_next_line.c ft_strsub.c ft_strncmp.c\
		ft_strequ.c
OBJ = $(FILES:%.c=%.o)

all: $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJ): $(FILES)
	gcc $(CFL) $(FILES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
