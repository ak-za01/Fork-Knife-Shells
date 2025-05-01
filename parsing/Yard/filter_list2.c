/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:39:32 by noctis            #+#    #+#             */
/*   Updated: 2025/04/29 00:55:32 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_filter_list2(t_token **data)
{
	t_token	*ptr;
	int		f;

	if (!data || !*data)
		return (-1);
	ptr = *data;
	while (ptr)
	{
		f = ft_filter_search(ptr);
		if (f == 0)
			ptr = ptr->next;
		if (f == 1)
		{
			if (ft_filter_cas_1(&ptr) == -1)
				return (-1);
		}
		if (f == 2)
		{
			if (ft_filter_cas_2(&ptr) == -1)
				return (-1);
		}
	}
	ft_free_arg_node2(data);
	return (0);
}

int	ft_filter_search(t_token *ptr)
{
	int	f1;
	int	f2;

	if (!ptr)
		return (0);
	f1 = 0;
	f2 = 0;
	while (ptr && ptr->type != pipe_t)
	{
		if (ptr->type == cmd_t || ptr->type == b_cmd_t)
		{
			f1 = 1;
		}
		if (0 < ptr->type && ptr->type <= 5)
		{
			f2 = 1;
		}
		ptr = ptr->next;
	}
	if (f1 == 1 && f2 == 1)
		return (1);
	if (f1 == 0 && f2 == 1)
		return (2);
	return (0);
}

int	ft_filter_cas_1(t_token **ptr)
{
	t_token	*tmp1;
	int		count;
	int		i;

	i = 0;
	tmp1 = *ptr;
	count = ft_count_arg_node(tmp1, 2);
	while (tmp1 && !(tmp1->type == cmd_t || tmp1->type == b_cmd_t))
		tmp1 = tmp1->next;
	tmp1->c_red = malloc((count + 1) * sizeof(char *));
	if (!tmp1->c_red)
		return (-1);
	while (*ptr && (*ptr)->type != pipe_t)
	{
		if (!((*ptr)->type == cmd_t || (*ptr)->type == b_cmd_t))
		{
			tmp1->c_red[i] = ft_strdup((*ptr)->value);
			if (!tmp1->c_red[i])
				return (-1);
			i++;
		}
		(*ptr) = (*ptr)->next;
	}
	tmp1->c_red[i] = NULL;
	return (0);
}

int	ft_filter_cas_2(t_token **ptr)
{
	t_token	*tmp1;
	int		count;
	int		i;

	i = 0;
	tmp1 = *ptr;
	count = ft_count_arg_node(tmp1, 2);
	(*ptr)->c_red = malloc((count + 1) * sizeof(char *));
	if (!(*ptr)->c_red)
		return (-1);
	while (tmp1 && tmp1->type != pipe_t)
	{
		(*ptr)->c_red[i] = ft_strdup(tmp1->value);
		if (!(*ptr)->c_red[i])
			return (-1);
		i++;
		tmp1 = tmp1->next;
	}
	free((*ptr)->value);
	(*ptr)->value = NULL;
	(*ptr)->type = cmd_t;
	(*ptr)->c_red[i] = NULL;
	(*ptr) = tmp1;
	return (0);
}

void	ft_free_arg_node2(t_token **data)
{
	t_token	*ptr;
	t_token	*tmp;

	ptr = *data;
	while (ptr)
	{
		tmp = ptr->next;
		if (0 < ptr->type && ptr->type < 6)
		{
			if (ptr->prev)
				ptr->prev->next = tmp;
			else
				*data = tmp;
			if (tmp)
				tmp->prev = ptr->prev;
			if (ptr->value)
				free(ptr->value);
			if (ptr->c_arg)
				ft_free(ptr->c_arg);
			if (ptr->c_red)
				ft_free(ptr->c_red);
			free(ptr);
		}
		ptr = tmp;
	}
}
