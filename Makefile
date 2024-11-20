CC = cc
LIBFT = ../libft
FLAGS = -Wall -Wextra -Werror -g
NAME = minishell
SUPPRESSION_FILE = readline.supp

SRC = main.c \
	  ft_free_tab.c \
	  ft_print_tab.c \
	  ft_builtin_cmd.c \
	  ft_handle_signals.c \
	  ft_isnumber.c \
	  builtins.c \
	  ft_reverse_strtok.c \
	  ft_sub_chainechr.c \
	  ft_print_tree.c \
	  ft_nodeiter.c \
	  ft_create_tree.c \
	  ft_is_inner_quote.c \
	  ft_free_tree.c \
	  ft_is_in_set.c \
	  ft_tokenization.c \
	  check_builtins.c \
	  ft_split_ignore_quote.c \
	  split_ignore_quote.c \
	  ft_export.c \
	  ft_unset.c \
	  get_argument.c \
	  ft_is_whitespace.c \
	  get_line.c \
	  dollar.c \
	  environment.c \
	  separation.c \
	  tools.c \
	  execution.c \
	  redirections.c \

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

$(SUPPRESSION_FILE) :
	@echo "{\n\tleak readline\n\tMemcheck:Leak\n\t...\n\tfun:readline\n}" > $(SUPPRESSION_FILE)
	@echo "{\n\tleak add_history\n\tMemcheck:Leak\n\t...\n\tfun:add_history\n}" >> $(SUPPRESSION_FILE)

valgrind : $(NAME) $(SUPPRESSION_FILE)
	valgrind --suppressions=$(SUPPRESSION_FILE) --leak-check=full --show-leak-kinds=all ./$(NAME)

clean :
	@rm -rf obj
	@make clean -C libft/

fclean : clean
	@rm -f $(NAME) $(SUPPRESSION_FILE)
	@make fclean -C libft/

list :
	@ls -l *.c

re : fclean all

vpath %.o obj
vpath $(OBJ) obj

.PHONY : all clean fclean re obj_file list
