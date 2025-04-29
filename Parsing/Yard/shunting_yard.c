/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:43:02 by noctis            #+#    #+#             */
/*   Updated: 2025/04/29 01:02:16 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

void	ft_shunting_yard(t_token **data)
{
	t_token	*a;
	t_token	*b;

	a = NULL;
	b = NULL;
	set_precedence(data);
	while (*data)
		ft_move_list_shunting_yard(data, &a, &b);
	while (b)
		ft_pop(&b, &a);
	(ft_free_list(&b), ft_free_list(data));
	*data = a;
	return ;
}

void	set_precedence(t_token **data)
{
	t_token	*ptr;

	if (!data)
		return ;
	ptr = (*data);
	while (ptr)
	{
		if (ptr->type == 0)
			ptr->prec = pipe_p;
		else
			ptr->prec = string_p;
		ptr = ptr->next;
	}
}
