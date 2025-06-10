/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/09 22:21:20 by noctis           ###   ########.fr       */
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

void	signal_init(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*data;
	t_extra	x;

	atexit(leaks);
	(void)ac, (void)av;
	// signal_init();
	init_extra(&x, env);
	while (1)
	{
		str = readline(MAGENTA "minishell > " RESET);
		if (str && ft_check_string(str))
		{
			data = ft_parse(str, &x);
			if (data)
			{
				ft_print_list(data);
				// exec_cmd(data, &x);
				ft_free_list(&data);
			}
			// printf("\n > exit status : %d < \n", x.exit_status);
			add_history(str);
		}
		else if (!str)
			break ;
		free(str);
	}
	free_env_list(&x);
	return (x.exit_status);
}
