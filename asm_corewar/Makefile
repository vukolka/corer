NAME = asm

SRC = *.c
O_FILE = $(SRC:.c=.o)

INC = ./

FLAGS = -Wall -Werror -Wextra -O2

all: $(NAME)

$(NAME):
	make -C ./minilib/
	gcc $(FLAGS) -I $(INC) -c *.c
	gcc -o $(NAME) $(O_FILE) minilib/minilib.a

clean:
	make clean -C ./minilib/
	rm -rf $(O_FILE)

fclean: clean
	make fclean -C ./minilib/
	rm -rf $(NAME)

re: clean all
