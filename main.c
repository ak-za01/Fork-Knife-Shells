/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/27 07:45:03 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/main.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*data;
	t_env	*env_list;

	atexit(leaks);
	env_list = create_env_list(env);
	while (1)
	{
		str = readline(MAGENTA"minishell-> "RESET);
		if (str && str[0])
		{
			data = ft_parse(str);
			data->env_list = env_list;
			// ft_print_list(data);
			// printf("exec_builtin: %s and the token is: %d\n", data->value, data->type);
			if (data->type == b_cmd_t)
				exec_builtin(data);
			add_history(str);
			ft_free_list(&data);
		}
		else if (!str)
			break ;
		free(str);
	}
	return (0);
}
