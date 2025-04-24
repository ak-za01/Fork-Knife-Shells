/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:15:07 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/24 21:33:39 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/parse.h"

t_token *	ft_parse(char *str)
{
	t_token	*data;

	data = NULL;
	if (ft_tokenize(str, &data) < 0)
	{
		ft_free_list(&data);
		return NULL;
	}
	
	// ft_shunting_yard(&data) ;

	

	// ft_print_list3(data);
	return data;
}
