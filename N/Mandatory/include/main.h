/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:26 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/30 16:59:31 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../42_Libft/libft.h"
# include "./parse.h"
# include "./builtins.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# define RED "\e[1;31m"
# define CYAN "\e[1;36m"
# define YELLOW "\e[33m"
# define MAGENTA "\e[1;35m"
# define GREEN "\e[1;32m"
# define BLUE "\e[1;34m"
# define WHITE "\e[1;37m"
# define GRAY "\e[1;90m"

# define RESET "\e[0m"

// Global signal variable
extern volatile sig_atomic_t	g_signal_received;
// extern int						rl_catch_signals;

//------------------------------ Main :
int								main(int ac, char **av, char **env);

#endif
