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

all:
	@make -C corewar_main/
	@make -C asm_corewar/
	@cmake corewar_visualization/CMakeLists.txt
	@make -C corewar_visualization/
	cp corewar_main/corewar .
	cp asm_corewar/asm .
	cp corewar_visualization/CorewarVis .

clean:
	@make -C corewar_main/ clean
	@make -C asm_corewar/ clean

fclean:
	@make -C corewar_main/ fclean
	@make -C asm_corewar/ fclean
	@rm CorewarVis
	@rm asm
	@rm corewar

re: fclean all

.PHONY: all clean fclean re
.NOTPARALLEL: all $(NAME) clean fclean re