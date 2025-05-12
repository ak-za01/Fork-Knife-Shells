/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_cas_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:54:04 by noctis            #+#    #+#             */
/*   Updated: 2025/05/12 11:47:26 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

void	ft_set_mini_tokens(t_token **new)
{
	t_token	*ptr;

	ptr = *new;
	while (ptr)
	{
		ptr->type = cmd_arg_t;
		ptr->f = 1;
		ptr = ptr->next;
	}
	return ;
}

void	ft_connect_list(t_token *prev, t_token *next, t_token *new,
		t_token **data)
{
	t_token	*last;

	if (prev)
	{
		prev->next = new;
		new->prev = prev;
	}
	else
		*data = new;
	last = ft_last_list(new);
	if (next)
	{
		last->next = next;
		next->prev = last;
	}
}

int	ft_add_nodes(char *t, t_token *ptr, t_token **data)
{
	t_token	*new;
	t_token	*tmp;
	t_token	*next;
	t_token	*prev;

	new = NULL;
	next = ptr->next;
	prev = ptr->prev;
	if (ft_initialize_list(t, &new) < 0)
		return (-1);
	if (ft_remove_end_token(&new) == -1)
		return (ft_free_list(&new), -1);
	ft_set_mini_tokens(&new);
	ft_connect_list(prev, next, new, data);
	tmp = ptr;
	ptr = next;
	free(tmp->value);
	free(tmp);
	return (0);
}

int	ft_handle_cas_1(t_token **data, t_token *ptr)
{
	int		s;
	char	**t;

	t = ft_split(ptr->value, ' ');
	if (!t)
		return (-1);
	s = ft_strlen_2(t);
	if (ptr->prev && (0 < ptr->prev->type && ptr->prev->type < 5))
	{
		if (s > 1)
			ptr->type = ambiguous_t;
	}
	else if (!ptr->prev || (ptr->prev && !(0 < ptr->prev->type
				&& ptr->prev->type < 5)))
	{
		if (ft_add_nodes(ptr->value, ptr, data) < 0)
			return (-1);
	}
	ft_free(t);
	return (1);
}
