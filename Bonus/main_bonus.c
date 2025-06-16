/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/16 21:29:17 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main_bonus.h"

volatile sig_atomic_t g_signal_received = 0;

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*data;
	t_extra	x;

	// atexit(leaks);
	(void)ac, (void)av;
	// signal_init_interactive();
	init_extra(&x, env);
	while (1)
	{
		str = readline(MAGENTA "minishell > " RESET);
		// handle_signal_in_main();
		if (str && ft_check_string(str))
		{
			data = ft_parse(str, &x);
			if (data)
			{
				// ft_print_list(data);
				exec_cmd(data, &x);
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
