/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/22 07:09:58 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"
#include "./include/parse.h"
#include "./include/builtins.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_env	*env_list;
	int		i;

	i = 0;
	env_list = create_env_list(env);
	while (i < 1)
	{
		str = readline("minishell> ");
		if (str && str[0])
		{
			// ft_parse(str);
			if (is_builtin(str))
				exec_builtin(ft_split(str, ' '), &env_list);
			add_history(str);
		}
		else if(!str)
		{
			printf("\n");
			printf("exit\n");
			free(str);
			break;
		}
		// i++;
	}
	return (0);
}
