#               ----------------      MAC :    ----------------

CC = cc

# CFLAGS = -Wall -Werroro -Wextra -I./readline/include

# CFLAGS = -fsanitize=address -g -I./libs/readline/include

CFLAGS = -I./libs/readline/include

RDFLAGS = -L./libs/readline/lib -lreadline


#               ----------------      LNX :    ----------------


# CC = cc

# # CFLAGS = -Wall -Werroro -Wextra -I./readline/include

# # CFLAGS = -fsanitize=address -g -I./libs/readline/include

# CFLAGS = -I./libs/readline/include

# RDFLAGS = -lreadline -lncurses


#               ----------------                ----------------


headers  = ./include/main.h \
			./include/parse.h \

SRC  = ./main.c \
		./utils_delet.c \
		./parsing/parse.c \
		./parsing/tokenize/tokenize.c \
		./parsing/tokenize/list.c \
		./parsing/Yard/shunting_yard.c  \
		./parsing/Yard/list.c  \
		./parsing/utils/ft_split2.c \
		./parsing/utils/ft_split3.c \
		./parsing/utils/utils1.c \

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