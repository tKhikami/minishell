CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = minishell
SRC = main.c
OBJ = $(SRC:.c=.o)

####################### VARIABLES ###########################

all: obj_file $(NAME)

obj_file:
	mkdir -p obj

%.o: %.c
	$(CC) $(FLAGS) -o ./obj/$@ -c $<

$(NAME): $(OBJ)
	cd obj && $(CC) $(FLAGS) $(OBJ) -o ../$(NAME)

clean:
	@rm -Rf obj

fclean: clean
	@rm -f $(NAME)

list:
	@ls -l *.c

re: fclean all

vpath %.o obj
vpath $(OBJ) obj

.PHONY: all clean fclean re obj_file list
