/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/06 21:49:26 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*data;
	t_env	*env_list;

	atexit(leaks);
	env_list = create_env_list(env);
	((void)ac, (void)av);
	while (1)
	{
		str = readline(MAGENTA "Minishell > " RESET);
		if (str && str[0])
		{
			data = ft_parse(str);
			if (data)
			{
				data->env_list = env_list;
				// ft_print_list(data);
				if (data->type == b_cmd_t)
				exec_builtin(data);
				add_history(str);
				ft_free_list(&data);
			}
		}
		else if (!str)
			break ;
		free(str);
	}
	free_env_list(&env_list);
	return (0);
}
