/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 05:13:55 by noctis            #+#    #+#             */
/*   Updated: 2025/07/01 13:17:55 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft__is_marque(char *t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		if (t[i] == '\x1F')
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_size2(char **t)
{
	int	i;
	int	s;
	int	count;

	i = 0;
	s = 0;
	count = 0;
	while (t[i])
	{
		if (ft__is_marque(t[i]))
		{
			s = ft_strlen(t[i]);
			count = count + (s - 4);
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

void	ft_copy_withe_no_q2(char *rs, char **t, int i, int k)
{
	size_t	j;
	size_t	len;

	while (t[i])
	{
		if (ft__is_marque(t[i]))
		{
			len = ft_strlen(t[i]);
			if (len >= 4)
			{
				j = 2;
				while (j < len - 2)
					rs[k++] = t[i][j++];
			}
		}
		else
		{
			j = 0;
			while (t[i][j])
				rs[k++] = t[i][j++];
		}
		i++;
	}
	rs[k] = '\0';
}

char	*ft_remove_q2(char *str)
{
	int		s;
	char	*rs;
	char	**t;

	t = ft_split4(str);
	if (!t)
		return (NULL);
	s = ft_count_size2(t);
	rs = malloc(s + 1);
	if (!rs)
		return (ft_free(t), free(str), str = NULL, NULL);
	ft_copy_withe_no_q2(rs, t, 0, 0);
	return (ft_free(t), free(str), str = NULL, rs);
}

int	ft_remove_quotes2(t_token **data)
{
	char	*t;
	t_token	*ptr;

	ptr = *data;
	while (ptr && ptr->type != end_t)
	{
		if (ptr->prev && ptr->prev->type == heredoc_t)
		{
			ptr = ptr->next;
			continue ;
		}
		else
		{
			if (ptr->value && ptr->f == 1 && ft__is_marque(ptr->value))
			{
				t = ft_strdup(ptr->value);
				free(ptr->value);
				ptr->value = ft_remove_q2(t);
				if (!ptr->value)
					return (free(t), -1);
			}
			ptr = ptr->next;
		}
	}
	return (0);
}
