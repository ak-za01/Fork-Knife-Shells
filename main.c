/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/09 19:07:48 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"
#include "./include/parse.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	int		i;

	// atexit(leaks);
	// i = 0;
	// while (i < 1)
	// {
	// 	str = readline("Minishell > ");
	// 	if (str && str[0])
	// 	{
	// 		ft_parse(str);
	// 		add_history(str);
	// 	}
	// 	else if(!str) 
	// 		break ;
	// 	free(str);
	// 	i++;
	// }
	//  char **t=ft_split3("hellothis is me");
	print_tab(ft_split3("ls |cat|<< >>< |< f"));
    // print_tab(t);
	return (0);
}
