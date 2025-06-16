#               ----------------      MAC :    ----------------

CC = cc

CFLAGS = -Wall -Werror -Wextra -I./../readline/include

# CFLAGS = -fsanitize=address -g -I./libs/readline/include

# CFLAGS = -I./libs/readline/include

RDFLAGS = -L./../readline/lib -lreadline


#               ----------------      LNX :    ----------------


# CC = cc

# # CFLAGS = -Wall -Werror -Wextra -I./libs/readline/include

# CFLAGS = -fsanitize=address -g -I./libs/readline/include

# # CFLAGS = -I./libs/readline/include

# RDFLAGS = -lreadline -lncurses


#               ----------------                ----------------


headers  =	./include/main_bonus.h \
			./include/parse_bonus.h \
			./include/builtins_bonus.h \

PARSING  =	./main_bonus.c \
			./utils_delet_bonus.c \
			./Parsing/parse_bonus.c \
			./Parsing/Tokenize/tokenize_bonus.c \
			./Parsing/Tokenize/set_token_bonus.c\
			./Parsing/Tokenize/validate_list_bonus.c \
			./Parsing/Tokenize/list_bonus.c \
			./Parsing/Exp/expand_bonus.c \
			./Parsing/Exp/swap_value_bonus.c \
			./Parsing/Exp/swap_utils_bonus.c \
			./Parsing/Exp/swap_utils2_bonus.c \
			./Parsing/Exp/fix_list_bonus.c \
			./Parsing/Exp/fix_cas_1_bonus.c \
			./Parsing/Exp/fix_cas_2_bonus.c \
			./Parsing/Exp/set_token_bonus.c \
			./Parsing/Exp/quotes_bonus.c \
			./Parsing/Exp/utils_bonus.c \
			./Parsing/Wildcard/wildcard_bonus.c \
			./Parsing/Wildcard/get_wc_list_bonus.c \
			./Parsing/Wildcard/files_list_bonus.c \
			./Parsing/Wildcard/cmd_list_bonus.c \
			./Parsing/Wildcard/filter_list_bonus.c \
			./Parsing/Wildcard/fix_wc_list_bonus.c \
			./Parsing/Filter/filter_list_bonus.c  \
			./Parsing/Filter/filter_list2_bonus.c  \
			./Parsing/Utils/ft_split2_bonus.c \
			./Parsing/Utils/ft_split3_bonus.c \
			./Parsing/Utils/ft_split4_bonus.c \
			./Parsing/Utils/ft_split5_bonus.c \
			./Parsing/Utils/ft_strjoin4_bonus.c \
			./Parsing/Utils/utils1_bonus.c \

BUILTINS =	./execution/builtins/builtins_bonus.c \
			./execution/builtins/cd_bonus.c \
			./execution/builtins/echo_bonus.c \
			./execution/builtins/environment_bonus.c \
			./execution/builtins/exit_bonus.c \
			./execution/builtins/export_bonus.c \
			./execution/builtins/unset_bonus.c \
			./execution/builtins_utils/cd_utils_bonus.c \
			./execution/builtins_utils/export_utils_bonus.c \
			./execution/builtins_utils/export_utils2_bonus.c \
			./execution/builtins_utils/split_env_bonus.c \

EXEC = 		./execution/exec/execution_bonus.c \
			./execution/exec/exec_single_bonus.c \
			./execution/exec/helpers_bonus.c \
			./execution/exec/helpers2_bonus.c \
			./execution/exec/redirection_bonus.c \
			./execution/exec/heredoc_bonus.c \
			./execution/exec/pipe_bonus.c \
			./execution/signals_bonus.c \

EXECUTION = ${BUILTINS} \
			${EXEC} \

SRC =	${PARSING} \
		${EXECUTION} \

OBJC = $(SRC:%.c=%.o)

libft_Dir = ./libs/42_Libft
libft = $(libft_Dir)/libft.a

NAME = ../minishell_bonus

all: $(NAME)

$(NAME): $(OBJC)
	@make -C $(libft_Dir)
	@$(CC) $(CFLAGS) $(OBJC) -o $(NAME) $(libft) $(RDFLAGS) && ./$(NAME)

%.o: %.c $(headers)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(libft_Dir) clean
	@rm -rf $(OBJC) 

fclean: clean
	@make -C $(libft_Dir) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re