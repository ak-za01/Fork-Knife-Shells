/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:26 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/24 16:43:10 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <fcntl.h>

# include <unistd.h>
# include <stdlib.h>

# include "../libs/42_Libft/libft.h"

# ifdef __linux__
#  include <readline/history.h>
#  include <readline/readline.h>
# else
#  include "../libs/readline/history.h"
#  include "../libs/readline/readline.h"
# endif

#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define MAGENTA	"\033[1;35m"
#define RESET   "\033[0m"


int		main(int ac, char **av, char **env);

// delet later :
#include "./parse.h"
void	leaks(void);
void ft_print_list(t_token *data);
void print_tab(char **t);
void	ft_print_list2(t_token *data);
void	ft_print_list3(t_token *data);






#endif

/*
	to conufigur readline in mac  :

		cd readline
		./configure --prefix=$(pwd)
		make && make install

*/