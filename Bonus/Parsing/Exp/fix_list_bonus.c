/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_list_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:37:24 by noctis            #+#    #+#             */
/*   Updated: 2025/06/16 21:30:53 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

void	ft_free_arg_node3(t_token **data)
{
	int		s;
	t_token	*ptr;
	t_token	*tmp;

	ptr = *data;
	while (ptr)
	{
		s = ft_get_node_count(ptr);
		tmp = ptr->next;
		if (ptr->type == free_t && s > 0)
		{
			if (ptr->prev)
				ptr->prev->next = tmp;
			else
				*data = tmp;
			if (tmp)
				tmp->prev = ptr->prev;
			if (ptr->value)
				free(ptr->value);
			free(ptr);
		}
		else if (ptr->type == free_t && s == 0)
			ptr->type = skip_t;
		ptr = tmp;
	}
}

int	ft_fix_list(t_token **data)
{
	t_token	*ptr;
	t_token	*tmp;

	ptr = *data;
	while (ptr->type != end_t)
	{
		tmp = ptr->next;
		if (ptr->f == 1)
		{
			if (ptr->value && ptr->value[0] != '\0')
			{
				if (ft_handle_cas_1(data, ptr) == -1)
					return (-1);
			}
			else if (!ptr->value || ptr->value[0] == '\0')
			{
				if (ft_handle_cas_2(ptr) == -1)
					return (-1);
			}
		}
		ptr = tmp;
	}
	ft_free_arg_node3(data);
	return (0);
}
