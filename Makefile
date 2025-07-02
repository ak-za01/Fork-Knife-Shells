CC = cc

CFLAGS = -Wall -Werror -Wextra -I$(HOME)/readline/include

# CFLAGS = -fsanitize=address -g -I$(HOME)/readline/include

LDFLAGS = -L$(HOME)/readline/lib

LDLIBS  = -lreadline -lncurses

# Mandatory 

headers  =	./Mandatory/include/main.h \
			./Mandatory/include/parse.h \
			./Mandatory/include/builtins.h \

PARSING  =	./Mandatory/main.c \
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
			./Mandatory/Parsing/Exp/quotes2.c \
			./Mandatory/Parsing/Exp/filter_exp.c \
			./Mandatory/Parsing/Exp/utils.c \
			./Mandatory/Parsing/Filter/filter_list.c  \
			./Mandatory/Parsing/Filter/filter_list2.c  \
			./Mandatory/Parsing/Utils/ft_split2.c \
			./Mandatory/Parsing/Utils/ft_split3.c \
			./Mandatory/Parsing/Utils/ft_split4.c \
			./Mandatory/Parsing/Utils/utils1.c \
			./Mandatory/Parsing/Utils/utils2.c \
			./Mandatory/Parsing/Utils/ft_strjoin4.c \

BUILTINS =	./Mandatory/execution/builtins/pwd.c \
			./Mandatory/execution/builtins/cd.c \
			./Mandatory/execution/builtins/echo.c \
			./Mandatory/execution/builtins/environment.c \
			./Mandatory/execution/builtins/exit.c \
			./Mandatory/execution/builtins/export.c \
			./Mandatory/execution/builtins/unset.c \
			./Mandatory/execution/builtins_utils/cd_utils.c \
			./Mandatory/execution/builtins_utils/cd_utils2.c \
			./Mandatory/execution/builtins_utils/export_utils.c \
			./Mandatory/execution/builtins_utils/export_utils2.c \
			./Mandatory/execution/builtins_utils/split_env.c \
			./Mandatory/execution/builtins_utils/env_utils.c \

EXEC = 		./Mandatory/execution/exec/execution.c \
			./Mandatory/execution/exec/exec_external.c \
			./Mandatory/execution/exec/exec_external_utils.c \
			./Mandatory/execution/exec/exec_external_utils2.c \
			./Mandatory/execution/exec/exec_single.c \
			./Mandatory/execution/exec/helpers.c \
			./Mandatory/execution/exec/redirection.c \
			./Mandatory/execution/exec/red_utils.c \
			./Mandatory/execution/exec/heredoc.c \
			./Mandatory/execution/exec/here_utils.c \
			./Mandatory/execution/exec/pipe.c \
			./Mandatory/execution/exec/pipe_utils.c \
			./Mandatory/execution/exec/pipe_utils2.c \
			./Mandatory/execution/signal/signals.c \
			./Mandatory/execution/signal/signals_utils.c \


EXECUTION = ${BUILTINS} \
			${EXEC} \

SRC =	${PARSING} \
		${EXECUTION} \

OBJC = $(SRC:%.c=%.o)

libft_DIR = ./Mandatory/42_Libft
libft = $(libft_DIR)/libft.a

# Bonus

headers_B  =	./Bonus/include/main_bonus.h \
			./Bonus/include/parse_bonus.h \
			./Bonus/include/builtins_bonus.h \

PARSING_B  =	./Bonus/main_bonus.c \
			./Bonus/Parsing/parse_bonus.c \
			./Bonus/Parsing/Tokenize/tokenize_bonus.c \
			./Bonus/Parsing/Tokenize/set_token_bonus.c\
			./Bonus/Parsing/Tokenize/validate_list_bonus.c \
			./Bonus/Parsing/Tokenize/list_bonus.c \
			./Bonus/Parsing/Exp/expand_bonus.c \
			./Bonus/Parsing/Exp/swap_value_bonus.c \
			./Bonus/Parsing/Exp/swap_utils_bonus.c \
			./Bonus/Parsing/Exp/swap_utils2_bonus.c \
			./Bonus/Parsing/Exp/fix_list_bonus.c \
			./Bonus/Parsing/Exp/fix_cas_1_bonus.c \
			./Bonus/Parsing/Exp/fix_cas_2_bonus.c \
			./Bonus/Parsing/Exp/set_token_bonus.c \
			./Bonus/Parsing/Exp/quotes_bonus.c \
			./Bonus/Parsing/Exp/quotes2_bonus.c \
			./Bonus/Parsing/Exp/filter_exp_bonus.c \
			./Bonus/Parsing/Exp/utils_bonus.c \
			./Bonus/Parsing/Wildcard/wildcard_bonus.c \
			./Bonus/Parsing/Wildcard/get_wc_list_bonus.c \
			./Bonus/Parsing/Wildcard/files_list_bonus.c \
			./Bonus/Parsing/Wildcard/cmd_list_bonus.c \
			./Bonus/Parsing/Wildcard/filter_list_bonus.c \
			./Bonus/Parsing/Wildcard/fix_wc_list_bonus.c \
			./Bonus/Parsing/Filter/filter_list_bonus.c  \
			./Bonus/Parsing/Filter/filter_list2_bonus.c  \
			./Bonus/Parsing/Utils/ft_split2_bonus.c \
			./Bonus/Parsing/Utils/ft_split3_bonus.c \
			./Bonus/Parsing/Utils/ft_split4_bonus.c \
			./Bonus/Parsing/Utils/ft_split5_bonus.c \
			./Bonus/Parsing/Utils/ft_strjoin4_bonus.c \
			./Bonus/Parsing/Utils/utils1_bonus.c \
			./Bonus/Parsing/Utils/utils2_bonus.c \

BUILTINS_B =	./Bonus/execution/builtins/pwd_bonus.c \
			./Bonus/execution/builtins/cd_bonus.c \
			./Bonus/execution/builtins/echo_bonus.c \
			./Bonus/execution/builtins/environment_bonus.c \
			./Bonus/execution/builtins/exit_bonus.c \
			./Bonus/execution/builtins/export_bonus.c \
			./Bonus/execution/builtins/unset_bonus.c \
			./Bonus/execution/builtins_utils/cd_utils_bonus.c \
			./Bonus/execution/builtins_utils/cd_utils2_bonus.c \
			./Bonus/execution/builtins_utils/export_utils_bonus.c \
			./Bonus/execution/builtins_utils/export_utils2_bonus.c \
			./Bonus/execution/builtins_utils/split_env_bonus.c \
			./Bonus/execution/builtins_utils/env_utils_bonus.c \

EXEC_B = 		./Bonus/execution/exec/execution_bonus.c \
			./Bonus/execution/exec/exec_external_bonus.c \
			./Bonus/execution/exec/exec_external_utils_bonus.c \
			./Bonus/execution/exec/exec_external_utils2_bonus.c \
			./Bonus/execution/exec/exec_single_bonus.c \
			./Bonus/execution/exec/helpers_bonus.c \
			./Bonus/execution/exec/redirection_bonus.c \
			./Bonus/execution/exec/red_utils_bonus.c \
			./Bonus/execution/exec/heredoc_bonus.c \
			./Bonus/execution/exec/here_utils_bonus.c \
			./Bonus/execution/exec/pipe_bonus.c \
			./Bonus/execution/exec/pipe_utils_bonus.c \
			./Bonus/execution/exec/pipe_utils2_bonus.c \
			./Bonus/execution/signal/signals_bonus.c \
			./Bonus/execution/signal/signals_utils_bonus.c \


EXECUTION_B = ${BUILTINS_B} \
			${EXEC_B} \


SRC_B =	${PARSING_B} \
		${EXECUTION_B} \

OBJC_B = $(SRC_B:%.c=%.o)

libft_DIR_B = ./BONUS/42_Libft
libft_B = $(libft_DIR_B)/libft.a

NAME = ./minishell
NAME_B = ./minishell_bonus

#	Colors

RESET		= \033[0m
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m

# ASCII Art Display Functions
define show_mandatory_banner
	@echo "$(PURPLE)"
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "$(YELLOW)"
	@echo "                    🐚 A Simple Shell Implementation 🐚"
	@echo "$(PURPLE)                      Created by anktiri & aakritah$(RESET)"
	@echo ""
endef

define show_bonus_banner
	@echo "$(GREEN)"
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "$(YELLOW)"
	@echo "                🌟 Minishell Bonus - With Wildcards! 🌟"
	@echo "$(PURPLE)                      Created by anktiri & aakritah$(RESET)"
	@echo ""
endef

all: $(NAME)

$(NAME): show_banner $(OBJC)
	@make -C $(libft_DIR)
	@echo "$(CYAN)🔗 Linking executable...$(RESET)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJC) -o $(NAME) $(libft) $(LDLIBS)
	@echo "$(GREEN)✅ Minishell compiled successfully!$(RESET)"

show_banner:
	$(call show_mandatory_banner)

Mandatory/%.o: Mandatory/%.c $(headers) $(libft_DIR)/libft.h
#	@echo "$(CYAN)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_B)

$(NAME_B): show_bonus_banner $(OBJC_B)
	@make -C $(libft_DIR_B)
	@echo "$(CYAN)🔗 Linking bonus executable...$(RESET)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJC_B) -o $(NAME_B) $(libft_B) $(LDLIBS)
	@echo "$(GREEN)✅ Minishell Bonus compiled successfully!$(RESET)"

show_bonus_banner:
	$(call show_bonus_banner)

Bonus/%.o: Bonus/%.c $(headers_B) $(libft_DIR_B)/libft.h
#	@echo "$(CYAN)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@make -C $(libft_DIR) clean
	@make -C $(libft_DIR_B) clean
	@rm -rf $(OBJC) 
	@rm -rf $(OBJC_B) 
	@echo "$(GREEN)✅ Clean completed!$(RESET)"

fclean: clean
	@echo "$(RED)🗑️  Full clean - removing executables...$(RESET)"
	@make -C $(libft_DIR) fclean
	@make -C $(libft_DIR_B) fclean
	@rm -rf $(NAME)
	@rm -rf $(NAME_B)
	@echo "$(GREEN)✅ Full clean completed!$(RESET)"

re: fclean all
	@echo "$(CYAN)🔄 Rebuild completed!$(RESET)"

.PHONY: all bonus clean fclean re show_banner show_bonus_banner