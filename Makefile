CC = cc

# CFLAGS = -Wall -Werror -Wextra -I./readline/include

# CFLAGS = -fsanitize=address -g -I./libs/readline/include

CFLAGS = -I./libs/readline/include

RDFLAGS = -L./libs/readline/lib -lreadline

headers  = ./include/main.h \
			./include/parse.h \

SRC  = ./main.c \
		./utils_delet.c \


OBJC = $(SRC:%.c=%.o)

libft_Dir = ./libs/42_libft
libft = $(libft_Dir)/libft.a

NAME = Minishell

all: $(NAME) clean

$(NAME): $(OBJC)
#	make -C $(libft_Dir)
	@$(CC) $(CFLAGS) $(OBJC) -o $(NAME) $(libft) $(RDFLAGS) && ./$(NAME)

%.o: %.c $(headers)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
#	make -C $(libft_Dir) clean
	@rm -rf $(OBJC) 

fclean: clean
#	make -C $(libft_Dir) fclean
	@rm -rf $(NAME)

re: fclean all

.phony: all clean fclean re