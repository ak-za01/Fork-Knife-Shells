/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:26 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/28 21:32:25 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H

# include "../42_Libft/libft.h"
# include "./parse_bonus.h"
# include "./builtins_bonus.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>

# ifdef __linux__
#  include <readline/history.h>
#  include <readline/readline.h>
# else
#  include "readline/history.h"
#  include "readline/readline.h"
# endif

# define RED "\033[1;31m"
# define CYAN "\033[1;36m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[1;35m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define WHITE "\033[1;37m"
# define GRAY "\033[0;90m"

# define RESET "\033[0m"

// Global signal variable
extern volatile sig_atomic_t	g_signal_received;

//------------------------------ Main :
int								main(int ac, char **av, char **env);

#endif

/*
	to conufigur readline in mac  :

		cd readline
		./configure --prefix=$(pwd)
		make && make install

*/