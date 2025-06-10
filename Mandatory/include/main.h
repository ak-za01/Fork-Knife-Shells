/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:26 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/09 19:07:49 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// delet later
# include "../libs/42_Libft/libft.h"
# include "./parse.h"
# include "./builtins.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef __linux__
#  include <readline/history.h>
#  include <readline/readline.h>
# else
#  include "../libs/readline/history.h"
#  include "../libs/readline/readline.h"
# endif

# define RED "\033[1;31m"
# define CYAN "\033[1;36m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[1;35m"
# define RESET "\033[0m"

//------------------------------ Main :
int		main(int ac, char **av, char **env);

//------------------------------ Delet Later :
void	leaks(void);
void	ft_print_list(t_token *data);
void	ft_print_list1(t_token *data);
void	ft_print_tab(char **t);

#endif

/*
	to conufigur readline in mac  :

		cd readline
		./configure --prefix=$(pwd)
		make && make install

*/