#               ----------------      MAC :    ----------------

CC = cc

CFLAGS = -Wall -Werror -Wextra -I./readline/include

# CFLAGS = -fsanitize=address -g -I./libs/readline/include

# CFLAGS = -I./libs/readline/include

RDFLAGS = -L./readline/lib -lreadline


#               ----------------      LNX :    ----------------


# CC = cc

# CFLAGS = -Wall -Werror -Wextra -I./libs/readline/include

# # CFLAGS = -fsanitize=address -g -I./libs/readline/include

# # CFLAGS = -I./libs/readline/include

# RDFLAGS = -lreadline -lncurses


#               ----------------                ----------------


headers  =	./Mandatory/include/main.h \
			./Mandatory/include/parse.h \
			./Mandatory/include/builtins.h \

PARSING  =	./Mandatory/main.c \
			./Mandatory/utils_delet.c \
			./Mandatory/Parsing/parse.c \
			./Mandatory/Parsing/Tokenize/tokenize.c \
			./Mandatory/Parsing/Tokenize/set_token.c\
			./Mandatory/Parsing/Tokenize/validate_list.c \
			./Mandatory/Parsing/Tokenize/list.c \
			./Mandatory/Parsing/Exp/expand.c \
			./Mandatory/Parsing/Exp/swap_value.c \
			./Mandatory/Parsing/Exp/swap_utils.c \
			./Mandatory/Parsing/Exp/swap_utils2.c \
			./Mandatory/Parsing/Exp/fix_list.c \
			./Mandatory/Parsing/Exp/fix_cas_1.c \
			./Mandatory/Parsing/Exp/fix_cas_2.c \
			./Mandatory/Parsing/Exp/set_token.c \
			./Mandatory/Parsing/Exp/quotes.c \
			./Mandatory/Parsing/Exp/utils.c \
			./Mandatory/Parsing/Filter/filter_list.c  \
			./Mandatory/Parsing/Filter/filter_list2.c  \
			./Mandatory/Parsing/Utils/ft_split2.c \
			./Mandatory/Parsing/Utils/ft_split3.c \
			./Mandatory/Parsing/Utils/ft_split4.c \
			./Mandatory/Parsing/Utils/utils1.c \

BUILTINS =	./Mandatory/execution/builtins/builtins.c \
			./Mandatory/execution/builtins/cd.c \
			./Mandatory/execution/builtins/echo.c \
			./Mandatory/execution/builtins/environment.c \
			./Mandatory/execution/builtins/exit.c \
			./Mandatory/execution/builtins/export.c \
			./Mandatory/execution/builtins/unset.c \
			./Mandatory/execution/builtins_utils/cd_utils.c \
			./Mandatory/execution/builtins_utils/export_utils.c \
			./Mandatory/execution/builtins_utils/export_utils2.c \
			./Mandatory/execution/builtins_utils/split_env.c \

EXEC = 		./Mandatory/execution/exec/execution.c \
			./Mandatory/execution/exec/exec_single.c \
			./Mandatory/execution/exec/helpers.c \
			./Mandatory/execution/exec/helpers2.c \
			./Mandatory/execution/exec/redirection.c \
			./Mandatory/execution/exec/heredoc.c \
			./Mandatory/execution/exec/pipe.c \
			./Mandatory/execution/signals.c \

EXECUTION = ${BUILTINS} \
			${EXEC} \

SRC =	${PARSING} \
		${EXECUTION} \

OBJC = $(SRC:%.c=%.o)

libft_Dir = ./Mandatory/libs/42_Libft
libft = $(libft_Dir)/libft.a

NAME = minishell

all: $(NAME)

bonus:
	make -C ./Bonus

$(NAME): $(OBJC)
	@make -C $(libft_Dir)
	@$(CC) $(CFLAGS) $(OBJC) -o $(NAME) $(libft) $(RDFLAGS) && ./$(NAME)

%.o: %.c $(headers)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(libft_Dir) clean
	@make -C ./Bonus clean
	@rm -rf $(OBJC) 

fclean: clean
	@make -C $(libft_Dir) fclean
	@make -C ./Bonus fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re


