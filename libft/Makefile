NAME = libft.a

SRC = ft_isascii.c ft_atoi.c ft_memcmp.c ft_putendl_fd.c ft_strdup.c ft_strncmp.c ft_tolower.c ft_bzero.c ft_isdigit.c ft_memcpy.c ft_putnbr_fd.c ft_strjoin.c ft_strnstr.c ft_toupper.c ft_calloc.c ft_isprint.c ft_memmove.c ft_putstr_fd.c ft_strlcat.c ft_strrchr.c ft_isalnum.c ft_itoa.c ft_memset.c ft_split.c ft_strlcpy.c ft_strtrim.c ft_isalpha.c ft_memchr.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_strchr.c ft_strlen.c ft_substr.c ft_printf.c ft_printf_tool.c

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

CFLAGS = -Wall -Wextra -Werror -g

CC = cc $(CFLAGS)

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(BONUS:.c=.o)

all : $(NAME)

bonus : $(NAME) $(OBJ_BONUS)
	ar -rcs $(NAME) $(OBJ_BONUS)

$(NAME) : $(OBJ)
	ar -rcs $(NAME) $(OBJ)

.c.o :
	$(CC) -o $@ -c $<

clean :
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean : clean
	rm -rf  $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
