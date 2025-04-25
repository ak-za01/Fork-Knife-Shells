CC = cc

# CFLAGS = -Wall -Werror -Wextra -I./readline/include

# CFLAGS = -fsanitize=address -g -I./libs/readline/include

CFLAGS =  -I$(brew --prefix readline)/include -I./libs/readline/include

headers  = ./include/main.h \
			./include/parse.h \
			./include/builtins.h \

SRC  = ./main.c \
		./utils_delet.c \
		execution/builtins.c


OBJC = $(SRC:%.c=%.o)

libft_Dir = ./libs/42_Libft
libft = $(libft_Dir)/libft.a

NAME = minishell

all: $(NAME) clean

$(NAME): $(OBJC)
#	make -C $(libft_Dir)
	@$(CC) $(CFLAGS) $(OBJC) -o $(NAME) $(libft) -lreadline && ./$(NAME)

%.o: %.c $(headers)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
#	make -C $(libft_Dir) clean
	@rm -rf $(OBJC) 

fclean: clean
#	make -C $(libft_Dir) fclean
	@rm -rf

re: fclean all

.phony: all clean fclean re
