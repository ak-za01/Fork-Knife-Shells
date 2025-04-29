#               ----------------      MAC :    ----------------

# CC = cc

# # CFLAGS = -Wall -Werror -Wextra -I./libs/readline/include

# # CFLAGS = -fsanitize=address -g -I./libs/readline/include

# CFLAGS = -I./libs/readline/include

# RDFLAGS = -L./libs/readline/lib -lreadline


#               ----------------      LNX :    ----------------


CC = cc

# CFLAGS = -Wall -Werror -Wextra -I./libs/readline/include

CFLAGS = -fsanitize=address -g -I./libs/readline/include

# CFLAGS = -I./libs/readline/include

RDFLAGS = -lreadline -lncurses


#               ----------------                ----------------


headers  = ./include/main.h \
			./include/parse.h \

SRC  = ./main.c \
		./utils_delet.c \
		./Parsing/parse.c \
		./Parsing/Tokenize/tokenize.c \
		./Parsing/Tokenize/set_token.c\
		./Parsing/Tokenize/validate_list.c \
		./Parsing/Tokenize/list.c \
		./Parsing/Yard/shunting_yard.c  \
		./Parsing/Yard/filter_list.c  \
		./Parsing/Yard/filter_list2.c  \
		./Parsing/Yard/moves.c  \
		./Parsing/Tree/tree.c  \
		./Parsing/Utils/ft_split2.c \
		./Parsing/Utils/ft_split3.c \
		./Parsing/Utils/utils1.c \

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