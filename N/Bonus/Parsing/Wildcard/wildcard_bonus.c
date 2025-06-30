/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:26:33 by noctis            #+#    #+#             */
/*   Updated: 2025/06/16 21:32:31 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

int	ft_check_wc_string(char *t)
{
	int	i;

	i = 0;
	if (!t)
		return (0);
	while (t[i])
	{
		if (t[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

int	ft_wildcard(t_token **data)
{
	char	**t;
	t_token	*ptr;

	ptr = *data;
	while (ptr && ptr->type != end_t)
	{
		if (ft_check_wc_string(ptr->value) && (!ptr->prev || (ptr->prev
					&& ptr->prev->type != heredoc_t)))
		{
			t = ft_get_wc_list(ptr->value);
			if (!t)
				return (-1);
			if (ft_fix_wc_list(data, &ptr, t) < 0)
				return (ft_free(t), -1);
			ft_free(t);
		}
		else
			ptr = ptr->next;
	}
	if (ft_re_tokenizing(data) < 0)
		return (-1);
	return (0);
}
