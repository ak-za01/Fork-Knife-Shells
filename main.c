/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/24 20:59:25 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"
#include "./include/parse.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*data;

	atexit(leaks);
	while (1)
	{
		str = readline(MAGENTA"Minishell > "RESET);
		if (str && str[0])
		{
			data=ft_parse(str);
			ft_print_list(data);
			add_history(str);
			ft_free_list(&data);
		}
		else if (!str)
			break ;
		free(str);
	}
	return (0);
}
