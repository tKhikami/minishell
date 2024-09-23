CC = cc
LIBFT = ../libft
FLAGS = -Wall -Wextra -Werror -g
NAME = minishell

SRC = main.c \
	  ft_free_tab.c \
	  ft_print_tab_char.c \
	  ft_builtin_cmd.c \
	  ft_handle_signals.c \
	  ft_isnumber.c \
	  builtins.c \
	  ft_reverse_strtok.c \
	  ft_sub_chainechr.c \
	  ft_print_tree.c \
	  ft_nodeiter.c \
	  ft_create_node.c \
	  ft_is_inner_quote.c \

OBJ = $(SRC:.c=.o)

####################### VARIABLES ###########################

all : obj_file $(NAME)
	./$(NAME)

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
