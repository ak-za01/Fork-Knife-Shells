#               ----------------      MAC :    ----------------

# CC = cc

# # CFLAGS = -Wall -Werror -Wextra -I./libs/readline/include

# # CFLAGS = -fsanitize=address -g -I./libs/readline/include

# CFLAGS = -I./libs/readline/include

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
			./Parsing/parse.c \
			./Parsing/Tokenize/tokenize.c \
			./Parsing/Tokenize/set_token.c\
			./Parsing/Tokenize/validate_list.c \
			./Parsing/Tokenize/list.c \
			./Parsing/Exp/expand.c \
			./Parsing/Exp/swap_value.c \
			./Parsing/Exp/swap_utils.c \
			./Parsing/Exp/swap_utils2.c \
			./Parsing/Exp/fix_list.c \
			./Parsing/Exp/fix_cas_1.c \
			./Parsing/Exp/fix_cas_2.c \
			./Parsing/Exp/set_token.c \
			./Parsing/Exp/quotes.c \
			./Parsing/Exp/utils.c \
			./Parsing/Filter/filter_list.c  \
			./Parsing/Filter/filter_list2.c  \
			./Parsing/Utils/ft_split2.c \
			./Parsing/Utils/ft_split3.c \
			./Parsing/Utils/ft_split4.c \
			./Parsing/Utils/utils1.c \

BUILTINS =	./execution/builtins/builtins.c \
			./execution/builtins/cd.c \
			./execution/builtins/echo.c \
			./execution/builtins/environment.c \
			./execution/builtins/exit.c \
			./execution/builtins/export.c \
			./execution/builtins/unset.c \
			./execution/builtins_utils/cd_utils.c \
			./execution/builtins_utils/export_utils.c \
			./execution/builtins_utils/export_utils2.c \
			./execution/builtins_utils/split_env.c \

# EXEC = 		./execution/exec/execution.c \
# 			./execution/exec/exec_single.c \
# 			./execution/exec/helpers.c \
# 			./execution/exec/redirection.c \
# 			./execution/exec/heredoc.c \

EXECUTION = ${BUILTINS} \

SRC =	${PARSING} \
		${EXECUTION} \

OBJC = $(SRC:%.c=%.o)

libft_Dir = ./libs/42_Libft
libft = $(libft_Dir)/libft.a

NAME = minishell

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