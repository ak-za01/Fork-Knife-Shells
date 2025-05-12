/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:43:02 by noctis            #+#    #+#             */
/*   Updated: 2025/05/11 23:41:51 by noctis           ###   ########.fr       */
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
	ft_set_precedence(data);
	while (*data)
		ft_move_list_shunting_yard(data, &a, &b);
	while (b)
		ft_pop(&b, &a);
	(ft_free_list(&b), ft_free_list(data));
	*data = a;
	return ;
}

void	ft_set_precedence(t_token **data)
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

void	ft_move_list_shunting_yard(t_token **data, t_token **a, t_token **b)
{
	if ((*data)->prec == string_p)
	{
		ft_push(data, a);
	}
	else
	{
		if (!*b)
			ft_push(data, b);
		else
		{
			if ((*data)->prec > ft_last_list(*b)->prec)
				ft_push(data, b);
			else
			{
				while (*b && (*data)->prec <= ft_last_list(*b)->prec)
					ft_pop(b, a);
				ft_push(data, b);
			}
		}
	}
	return ;
}

void	ft_push(t_token **data, t_token **a)
{
	t_token	*ptr;
	t_token	*last;

	if (!data || !*data)
		return ;
	ptr = *data;
	(*data) = (*data)->next;
	if (*data)
		(*data)->prev = NULL;
	ptr->next = NULL;
	ptr->prev = NULL;
	if (!*a)
		*a = ptr;
	else
	{
		last = ft_last_list(*a);
		last->next = ptr;
		ptr->prev = last;
	}
}

void	ft_pop(t_token **b, t_token **a)
{
	t_token	*ptr;
	t_token	*last;

	if (!b || !*b || !a)
		return ;
	last = ft_last_list(*b);
	ptr = NULL;
	if (last->prev)
		last->prev->next = NULL;
	else
		*b = NULL;
	last->next = NULL;
	last->prev = NULL;
	if (!*a)
		*a = last;
	else
	{
		ptr = ft_last_list(*a);
		ptr->next = last;
		last->prev = ptr;
	}
}
