/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_cas_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:54:04 by noctis            #+#    #+#             */
/*   Updated: 2025/06/21 20:35:28 by anktiri          ###   ########.fr       */
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

int	ft_check_if_ambiguous(char *str)
{
	int		i;
	int		s;
	int		f;
	char	**t;

	t = ft_split4(str);
	if (!t)
		return (-1);
	i = 0;
	while (t[i])
	{
		f = ft_check_q_status(t[i]);
		s = ft_count_split2(t[i]);
		if (f == 0 && s > 1)
			return (ft_free(t), -2);
		i++;
	}
	return (ft_free(t), 0);
}

int	ft_handle_cas_1(t_token **data, t_token *ptr)
{
	int	f;

	if (ptr->prev && (1 < ptr->prev->type && ptr->prev->type < 5))
	{
		f = ft_check_if_ambiguous(ptr->value);
		if (f == -1)
			return (-1);
		else if (f == -2)
			ptr->type = ambiguous_t;
		else
			return (0);
	}
	else if (!ptr->prev || (ptr->prev && !(0 < ptr->prev->type
				&& ptr->prev->type < 5)))
	{
		if (ft_add_nodes(ptr->value, ptr, data) < 0)
			return (-1);
	}
	return (0);
}
