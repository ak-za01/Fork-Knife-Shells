/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:31:09 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/12 12:13:05 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_expanding_list(t_token **data, t_extra *x)
{
	char	*t;
	t_token	*ptr;

	ptr = *data;
	while (ptr->type != end_t)
	{
		if (ft_check(ptr->value))
			ptr->f = 1;
		t = ft_strdup(ptr->value);
		if (!t)
			return (-1);
		free(ptr->value);
		ptr->value = ft_swap_value(0, t, x);
		if (!ptr->value)
			return (-1);
		free(t);
		ptr = ptr->next;
	}
	return (0);
}

int	ft_expand(t_token **data, t_extra *x)
{
	t_token	*ptr;

	if (ft_expanding_list(data, x) < 0)
		return (-1);
	if (ft_fix_list(data) < 0)
		return (-1);
	ptr = *data;
	while (ptr && ptr->next && ptr->type != end_t)
	{
		if (ptr->type != ambiguous_t && ptr->type != skip_t)
			ptr->type = undefiend;
		ptr = ptr->next;
	}
	ft_set_tokens_after_expanding(data);
	ptr = *data;
	while (ptr && ptr->next && ptr->type != end_t)
	{
		if (ptr->type == ambiguous_t)
		{
			free(ptr->value);
			ptr->value = NULL;
		}
		ptr = ptr->next;
	}
	return (0);
}
