CC = cc
LIBFT = ../libft
FLAGS = -Wall -Wextra -Werror -g
NAME = minishell

SRC = main.c \

OBJ = $(SRC:.c=.o)

####################### VARIABLES ###########################

all : obj_file $(NAME)

obj_file :
	mkdir -p obj

%.o : %.c
	$(CC) $(FLAGS) -o ./obj/$@ -c $<

$(NAME) : $(OBJ)
	@make bonus -C libft/
	cd obj && $(CC) $(FLAGS) $(OBJ) -o ../$(NAME) -lreadline -L$(LIBFT) -lft

clean :
	@rm -rf obj
	@make clean -C libft/

fclean : clean
	@rm -f $(NAME)
	@make fclean -C libft/

list :
	@ls -l *.c

re : fclean all

vpath %.o obj
vpath $(OBJ) obj

.PHONY : all clean fclean re obj_file list
