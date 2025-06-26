/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:45:01 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/26 16:18:06 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void sig_handler_interactive(int signal)
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

void signal_init_interactive()
{
    struct sigaction sa;
    
    sa.sa_handler = sig_handler_interactive;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGPIPE, &sa, NULL);
    rl_catch_signals = 0;
}

void signal_init_exec()
{
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGPIPE, &sa, NULL);
}

void sig_handler_heredoc(int signal)
{
    g_signal_received = signal;
    if (signal == SIGINT)
    {
        rl_catch_signals = 0;
		// g_signal_received = 0;
        close(STDIN_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
}

void signal_init_heredoc()
{
    struct sigaction sa;
    
    sa.sa_handler = sig_handler_heredoc;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGPIPE, &sa, NULL);
    rl_catch_signals = 0;
}

void signal_init_child()
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGPIPE, SIG_DFL);
}

void handle_signal_in_main()
{
    if (g_signal_received == SIGINT)
	{}
        g_signal_received = 0;
}
