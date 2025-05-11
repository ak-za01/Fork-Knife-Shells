#               ----------------      MAC :    ----------------

# CC = cc

# CFLAGS = -Wall -Werror -Wextra -I./libs/readline/include

# # CFLAGS = -fsanitize=address -g -I./libs/readline/include

# # CFLAGS = -I./libs/readline/include

# RDFLAGS = -L./libs/readline/lib -lreadline


#               ----------------      LNX :    ----------------


CC = cc

# CFLAGS = -Wall -Werror -Wextra -I./libs/readline/include

# CFLAGS = -fsanitize=address -g -I./libs/readline/include

CFLAGS = -I./libs/readline/include

RDFLAGS = -lreadline -lncurses


#               ----------------                ----------------


headers  =	./include/main.h \
			./include/parse.h \
			./include/builtins.h \

PARSING  =	./main.c \
			./utils_delet.c \
			./parsing/parse.c \
			./parsing/tokenize/tokenize.c \
			./parsing/tokenize/set_token.c\
			./parsing/tokenize/validate_list.c \
			./parsing/tokenize/list.c \
			./parsing/Yard/shunting_yard.c  \
			./parsing/Yard/filter_list.c  \
			./parsing/Yard/filter_list2.c  \
			./parsing/utils/ft_split2.c \
			./parsing/utils/ft_split3.c \
			./parsing/utils/utils1.c \

EXECUTION =	./execution/builtins.c \
			./execution/echo.c \
			./execution/environment.c \
			./execution/split_env.c \
			./execution/export.c \

SRC =	${PARSING} \
		${EXECUTION} \

OBJC = $(SRC:%.c=%.o)

libft_Dir = ./libs/42_Libft
libft = $(libft_Dir)/libft.a

NAME = Minishell

all: $(NAME) clean

$(NAME): $(OBJC)
#	make -C $(libft_Dir)
	@$(CC) $(CFLAGS) $(OBJC) -o $(NAME) $(libft) $(RDFLAGS)  && ./$(NAME)

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