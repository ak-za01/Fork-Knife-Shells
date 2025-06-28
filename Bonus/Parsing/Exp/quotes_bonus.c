/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:21:54 by noctis            #+#    #+#             */
/*   Updated: 2025/06/16 21:30:57 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

int	ft_count_size(char **t)
{
	int	i;
	int	s;
	int	count;

	i = 0;
	s = 0;
	count = 0;
	while (t[i])
	{
		if (t[i][0] == '\"' || t[i][0] == '\'')
		{
			s = ft_strlen(t[i]);
			count = count + (s - 2);
		}
		else
		{
			s = ft_strlen(t[i]);
			count += s;
		}
		i++;
	}
	return (count);
}

void	ft_copy_withe_no_q(char *rs, char **t, int i, int k)
{
	size_t	j;

	while (t[i])
	{
		if (t[i][0] == '\"' || t[i][0] == '\'')
		{
			j = 1;
			while (j < ft_strlen(t[i]) - 1)
			{
				rs[k++] = t[i][j++];
			}
		}
		else
		{
			j = 0;
			while (t[i][j])
			{
				rs[k++] = t[i][j++];
			}
		}
		i++;
	}
	rs[k] = '\0';
}

char	*ft_remove_q(char *str)
{
	int		s;
	char	*rs;
	char	**t;

	t = ft_split4(str);
	if (!t)
		return (NULL);
	s = ft_count_size(t);
	rs = malloc(s + 1);
	if (!rs)
		return (ft_free(t), NULL);
	ft_copy_withe_no_q(rs, t, 0, 0);
	return (ft_free(t), free(str), rs);
}

int	ft_remove_quotes(t_token **data)
{
	char	*t;
	t_token	*ptr;

	ptr = *data;
	while (ptr && ptr->type != end_t)
	{
		if (ptr->f == 2 || (ptr->prev && ptr->prev->type == heredoc_t))
		{
			ptr = ptr->next;
			continue ;
		}
		else
		{
			if (ptr->value)
			{
				t = ft_strdup(ptr->value);
				free(ptr->value);
				ptr->value = ft_remove_q(t);
				if (!ptr->value)
					return (free(t), -1);
			}
			ptr = ptr->next;
		}
	}
	return (0);
}
