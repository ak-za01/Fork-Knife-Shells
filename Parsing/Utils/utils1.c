/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:59:30 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/09 18:43:31 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

void	ft_free(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}

void	ft_free2(char **t, int s)
{
	int	i;

	i = 0;
	while (i < s)
	{
		free(t[i]);
		i++;
	}
	free(t);
}

char	**ft_set_charset(void)
{
	char	**charset;

	charset = malloc(sizeof(char *) * 8);
	if (!charset)
		return (NULL);
	charset[0] = ">>";
	charset[1] = "<<";
	charset[2] = ">";
	charset[3] = "<";
	charset[4] = "|";
	charset[5] = "\"";
	charset[6] = "\'";
	charset[7] = NULL;
	return (charset);
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
