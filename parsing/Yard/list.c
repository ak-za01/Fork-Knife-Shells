/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:52:48 by noctis            #+#    #+#             */
/*   Updated: 2025/04/24 17:23:47 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

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