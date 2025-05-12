/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/12 17:41:41 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*data;
	t_extra	x;

	// atexit(leaks);
	((void)ac, (void)av);
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
	return (0);
}
