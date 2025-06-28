/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 07:10:20 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/20 09:46:07 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

t_token	*ft_creat_new_list(char *str, t_token_type type)
{
	t_token	*n;

	n = malloc(sizeof(t_token));
	if (!n)
		return (NULL);
	if (!str)
		n->value = NULL;
	else
		n->value = ft_strdup(str);
	n->type = type;
	n->f = 0;
	n->arg_s = 0;
	n->c_arg = NULL;
	n->red_s = 0;
	n->c_red = NULL;
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

void	ft_add_list_front(t_token **data, t_token *n)
{
	if (!data)
		return ;
	if (!*data)
	{
		*data = n;
		return ;
	}
	(*data)->prev = n;
	n->next = (*data);
	(*data) = n;
	return ;
}

void	ft_add_list_end(t_token **data, t_token *n)
{
	t_token	*ptr;

	if (!data)
		return ;
	if (!*data)
	{
		*data = n;
		return ;
	}
	ptr = (*data);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = n;
	n->prev = ptr;
	return ;
}

t_token	*ft_last_list(t_token *data)
{
	t_token	*ptr;

	if (!data)
		return (NULL);
	ptr = data;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void	ft_free_list(t_token **data)
{
	t_token	*ptr;

	if (!data)
		return ;
	while (*data)
	{
		ptr = (*data);
		(*data) = (*data)->next;
		if (ptr->value)
			free(ptr->value);
		if (ptr->c_arg)
			ft_free2(ptr->c_arg, ptr->arg_s);
		if (ptr->c_red)
			ft_free2(ptr->c_red, ptr->red_s);
		free(ptr);
	}
}
