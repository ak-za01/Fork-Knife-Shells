/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_cas_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:53:58 by noctis            #+#    #+#             */
/*   Updated: 2025/06/16 21:30:48 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

int	ft_get_node_count(t_token *ptr)
{
	int		s;
	t_token	*tmp;

	s = 0;
	tmp = ptr;
	while (tmp->prev && tmp->prev->type != pipe_t)
	{
		tmp = tmp->prev;
	}
	while (tmp->next && (tmp->next->type != pipe_t && tmp->next->type != end_t))
	{
		tmp = tmp->next;
		s++;
	}
	return (s);
}

int	ft_handle_cas_2(t_token *ptr)
{
	int	s;

	s = ft_get_node_count(ptr);
	if (ptr->prev && (1 < ptr->prev->type && ptr->prev->type < 5))
	{
		ptr->type = ambiguous_t;
	}
	else if (s == 0)
	{
		ptr->type = skip_t;
	}
	else
	{
		ptr->type = free_t;
	}
	return (1);
}
