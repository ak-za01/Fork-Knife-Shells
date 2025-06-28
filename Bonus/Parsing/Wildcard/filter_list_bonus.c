/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_list_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:59:03 by noctis            #+#    #+#             */
/*   Updated: 2025/06/16 21:32:21 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

int	ft_consume(char *t, int *i, t_wc *ptr, size_t s1)
{
	if (!ptr->prev)
	{
		if (ft_strncmp(t + (*i), ptr->value, s1) != 0)
			return (0);
		(*i) += s1;
	}
	else if (!ptr->next)
	{
		if (ft_strlen(t) < s1 || s1 + (*i) > ft_strlen(t))
			return (0);
		if (ft_strncmp(t + ft_strlen(t) - s1, ptr->value, s1) != 0)
			return (0);
		return (1);
	}
	else
	{
		while (t[(*i)] && ft_strncmp(t + (*i), ptr->value, s1) != 0)
			(*i)++;
		if (!t[(*i)])
			return (0);
		(*i) += s1;
	}
	return (2);
}

int	ft_valide(char *t, t_wc *data)
{
	int		i;
	int		f;
	t_wc	*ptr;

	i = 0;
	ptr = data;
	while (ptr)
	{
		if (ptr->f == 0)
		{
			f = ft_consume(t, &i, ptr, ft_strlen(ptr->value));
			if (f != 2)
				return (f);
		}
		else
		{
			if (!ptr->next)
				return (1);
		}
		ptr = ptr->next;
	}
	if (t[i])
		return (0);
	return (1);
}

int	ft_count_wc_match(char **t1, t_wc *data)
{
	int	i;
	int	count;
	int	f;

	i = 0;
	count = 0;
	while (t1[i])
	{
		f = ft_valide(t1[i], data);
		if (f == -1)
			return (-1);
		else if (f == 1)
			count++;
		i++;
	}
	return (count);
}

char	**ft_filter_wc_list(char **t1, t_wc *data, int i, int j)
{
	int		s;
	int		f;
	char	**t2;

	s = ft_count_wc_match(t1, data);
	if (s == -1)
		return (ft_free(t1), NULL);
	t2 = malloc((s + 1) * sizeof(char *));
	if (!t2)
		return (ft_free(t1), NULL);
	while (t1[i])
	{
		f = ft_valide(t1[i], data);
		if (f == -1)
			return (ft_free(t1), NULL);
		else if (f == 1)
		{
			t2[j] = ft_strdup(t1[i]);
			if (!t2[j])
				return (ft_free(t1), ft_free(t2), NULL);
			j++;
		}
		i++;
	}
	return (t2[j] = NULL, ft_free(t1), t2);
}
