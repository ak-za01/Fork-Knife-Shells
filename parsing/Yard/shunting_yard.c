/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:43:02 by noctis            #+#    #+#             */
/*   Updated: 2025/04/24 21:11:47 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

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
		else if (ptr->type == 9)
			ptr->prec = end_p;
		else if (0 < ptr->type && ptr->type < 5)
			ptr->prec = redirect_p;
		else
			ptr->prec = string_p;
		ptr = ptr->next;
	}
}


void	ft_shunting_yard(t_token **data)
{
	t_token	*a;
	t_token	*b;

	a = NULL;
	b = NULL;
	set_precedence(data);
	while ((*data)->next)
	{
		if ((*data)->prec == string_p)
		{
			ft_push(data, &a);
		}
		else
		{
			if (!b)
				ft_push(data, &b);
			else
			{
				if ((*data)->prec > ft_last_list(b)->prec)
					ft_push(data, &b);
				else
				{
					while (b && (*data)->prec <= ft_last_list(b)->prec)
						ft_pop(&b, &a);
					ft_push(data, &b);
				}
			}
		}
	}
	while (b)
		ft_pop(&b, &a);
	if ((*data)->type == end_t)
		ft_push(data, &a);
	ft_free_list(&b);
	ft_free_list(data);
	*data = a;
	return ;
}
