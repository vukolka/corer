# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoniev <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/04 17:39:23 by mkoniev           #+#    #+#              #
#    Updated: 2018/02/04 17:39:24 by mkoniev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
CC = gcc
FILES =	ft_print \
		
FLAGS = -Wall -Werror -Wextra -O3 -Os
SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
OBJ_LIST = $(addsuffix .o, $(FILES))
HEADERS = -I./includes

all: $(NAME)

$(NAME): libft/libft.a $(OBJ) 
	@echo "\033[36mLinking...\033[0m"
	@$(CC) -o $(NAME) $(OBJ) $(FLAGS) libft/libft.a
	@echo "\033[32m[ ✔ ] Binary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"
libft/libft.a:
	@make -C libft/
obj/%.o: src/%.c
	@$(CC) -o $@ $(FLAGS) $(HEADERS) -c $^
	@echo "\033[34mCompilation of \033[32m$(notdir $<) \033[0m\033[34mdone. \033[0m"
clean:
	@rm -rf $(OBJ)
	@make -C libft/ clean
	@echo "\033[31m[ ✔ ] Objects files \033[91m$(OBJ_LIST) \033[0m\033[31m removed. \033[0m"
fclean:
	@rm -rf $(OBJ)
	@rm -f $(NAME)
	@make -C libft/ fclean
	@echo "\033[31m[ ✔ ] Objects files \033[91m$(OBJ_LIST) \033[0m\033[31m removed. \033[0m"
	@echo "\033[31m[ ✔ ] Binary \033[1;31m$(NAME) \033[1;0m\033[31mremoved.\033[0m"
re: fclean all

.PHONY: all clean fclean re
.NOTPARALLEL: all $(NAME) clean fclean re