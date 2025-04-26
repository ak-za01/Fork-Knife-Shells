/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:47:36 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/26 15:17:03 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_filter_list(t_token **data)
{
	t_token	*ptr;

	ptr = *data;
	ft_remove_end_token(data);
	while (ptr)
	{
		if (ptr->type == cmd_t || ptr->type == b_cmd_t)
		{
			ptr->c_arg = malloc(sizeof(char *) * (ft_count_arg_node(ptr) + 1));
			if (!ptr->c_arg)
				return (-1);
			if (ft_copy_arg_node(ptr) == -1)
				return (-1);
		}
		ptr = ptr->next;
	}
	ft_free_arg_node(data);
	return (0);
}

void	ft_remove_end_token(t_token **data)
{
	t_token	*ptr;
	t_token	*tmp;

	ptr = *data;
	while (ptr->next && ptr->next->type != end_t)
		ptr = ptr->next;
	tmp = ptr->next;
	ptr->next = NULL;
	tmp->prev = NULL;
	tmp->next = NULL;
	ft_free_list(&tmp);
}

long	ft_count_arg_node(t_token *ptr)
{
	long	count;

	count = 1;
	while (ptr && ptr->type != pipe_t)
	{
		if (ptr->type == cmd_arg_t)
			count++;
		ptr = ptr->next;
	}
	return (count);
}

int	ft_copy_arg_node(t_token *ptr)
{
	long	i;
	t_token	*tmp;

	i = 0;
	tmp = ptr;
	while (tmp && tmp->type != pipe_t)
	{
		if (6 <= tmp->type && tmp->type <= 8)
		{
			ptr->c_arg[i] = ft_strdup(tmp->value);
			if (!ptr->c_arg[i])
				return (-1);
			i++;
		}
		tmp = tmp->next;
	}
	ptr->c_arg[i] = NULL;
	return (0);
}

void	ft_free_arg_node(t_token **data)
{
	t_token	*ptr;
	t_token	*tmp;

	ptr = *data;
	while (ptr)
	{
		tmp = ptr->next;
		if (ptr->type == cmd_arg_t)
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
		ptr = ptr->next;
	}
}
