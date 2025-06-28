/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:21:03 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/26 20:29:03 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	sig_handler_interactive(int signal)
{
	if (signal == SIGINT)
	{
		g_signal_received = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler_heredoc(int signal)
{
	g_signal_received = signal;
	if (signal == SIGINT)
	{
		rl_catch_signals = 0;
		close(STDIN_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}
