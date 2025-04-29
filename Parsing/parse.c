/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:15:07 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/29 02:00:24 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/parse.h"

t_token	*ft_parse(char *str)
{
	t_token	*data;
	t_ast	*tree;

	data = NULL;
	tree = NULL;
	if (ft_tokenize(str, &data) < 0)
	{
		ft_free_list(&data);
		return (NULL);
	}
	if (ft_filter_list(&data) < 0)
	{
		ft_free_list(&data);
		return (NULL);
	}
	if (ft_filter_list2(&data) < 0)
	{
		ft_free_list(&data);
		return (NULL);
	}
	// ft_shunting_yard(&data);
	// if (ft_tree(&data , &tree) < 0)
	// {
	// 	ft_free_list(&data);
	// 	ft_free_tree(&tree);
	// 	return (NULL);
	// }
	return (data);
}

/*

things to fix in parsing :

	echo "hello"'world'  : should be a whole world insted of 2

*/