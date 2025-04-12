/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/12 13:06:52 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"
#include "./include/parse.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	int		i;

	atexit(leaks);
	i = 0;
	// while (i<1)
	while (1)
	{
		str = readline("Minishell > ");
		if (str && str[0])
		{
			ft_parse(str);
			add_history(str);
		}
		else if (!str)
			break ;
		free(str);
		i++;
	}

	return (0);
}
