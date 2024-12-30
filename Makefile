CC = cc
LIBFT = ../libft
FLAGS = -Wall -Wextra -Werror -g
NAME = minishell
SUPPRESSION_FILE = readline.supp

SRC = main.c \
	  ft_print_tab.c \
	  ft_strtok.c \
	  signals.c \
	  ft_isnumber.c \
	  ft_cd.c \
	  ft_echo.c \
	  ft_env.c \
	  ft_env_utils.c \
	  ft_exit.c \
	  ft_export.c \
	  ft_pwd.c \
	  ft_unset.c \
	  ft_builtin_cmd.c \
	  my_strtok.c \
	  ft_substrchr.c \
	  ft_print_tree.c \
	  ft_nodeiter.c \
	  ft_create_tree.c \
	  ft_is_inner_quote.c \
	  ft_free_tree.c \
	  ft_is_in_set.c \
	  tokenization.c \
	  ft_split_ignore_quote.c \
	  split_ignore_quote.c \
	  ft_is_whitespace.c \
	  get_line.c \
	  dollar.c \
	  environment.c \
	  separation.c \
	  tools.c \
	  execution.c \
	  set_heredoc.c \
	  exit_status.c \
	  to_free.c

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
