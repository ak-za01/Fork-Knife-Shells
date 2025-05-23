/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/22 17:35:53 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_init()
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*data;
	t_extra	x;

	atexit(leaks);
	((void)ac, (void)av);
	signal_init();
	x.env_list = create_env_list(env);
	x.exit_status = 0;
	while (1)
	{
		str = readline(MAGENTA "Minishell > " RESET);
		if (str && str[0])
		{
			data = ft_parse(str, &x);
			if (data)
			{
				// ft_print_list(data);
				if (data->type == b_cmd_t)
					exec_builtin(data, x);
				ft_free_list(&data);
			}
			add_history(str);
		}
		else if (!str)
			break ;
		free(str);
	}
	free_env_list(&x);
	return (x.exit_status);
}
