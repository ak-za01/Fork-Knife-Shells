/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/07/02 16:31:26 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"

volatile sig_atomic_t	g_signal_received = 0;

int	main_engine(char *str, t_extra *x)
{
	t_token	*data;

	if (str && ft_check_string(str))
	{
		data = ft_parse(str, x);
		if (data)
		{
			x->exit_status = ft_execution(data, x);
			ft_free_list(&data);
		}
		add_history(str);
		return (1);
	}
	else if (!str)
	{
		ft_putstr_fd("exit\n", 1);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_extra	x;
	int		continue_loop;

	(void)ac, (void)av;
	signal_init_interactive();
	init_extra(&x, env);
	while (1)
	{
		str = readline(MAGENTA "minishell > " RESET);
		handle_signal_in_main(&x);
		continue_loop = main_engine(str, &x);
		if (!continue_loop)
			break ;
		if (str)
			free(str);
	}
	free_env_list(&x);
	return (x.exit_status);
}
