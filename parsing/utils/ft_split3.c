/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:45:20 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/26 21:10:01 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

static int	ft_check_t(char const *t, char **c)
{
	int	k;
	int	s;

	k = 0;
	while (c[k])
	{
		if (k < 2)
		{
			if ((t[0] && t[1]) && (t[0] == c[k][0]) && t[1] == c[k][1])
				return (k);
		}
		else
		{
			s = ft_strlen(c[k]);
			if (t[0] == c[k][0])
				return (k);
		}
		k++;
	}
	return (-1);
}

static int	ft_count(char const *str, char **charset)
{
	int		x;
	int		copy;
	int		k;
	int		f;
	int		i_c;
	char	q;

	x = 0;
	copy = 0;
	k = 0;
	f = 0;
	i_c = 0;
	while (str[x])
	{
		k = ft_check_t(str + x, charset);
		if ((k == 6 || k == 5) && i_c == 0)
		{
			q = str[x];
			i_c = !i_c;
		}
		else if (i_c == 1 && str[x] == q)
			i_c = !i_c;
		if (i_c == 0)
		{
			if (k == -1)
			{
				if (f == 0)
				{
					copy++;
					f = 1;
					x++;
				}
				else
					x++;
			}
			else if (k >= 0)
			{
				copy++;
				f = 0;
				x++;
				if (k < 2)
					x++;
			}
		}
		else
			x++;
	}
	return (copy);
}

static char	*ft_copy(char const *str, char **charset, int *x)
{
	int		k;
	int		i;
	int		y;
	char	q;
	char	*t;

	i = *x;
	k = ft_check_t(str + *x, charset);
	if (k == 5 || k == 6)
	{
		q = str[*x];
		(*x)++;
		while (str[*x] != q)
			(*x)++;
		(*x)++;
	}
	else if (2 <= k && k <= 4)
		(*x)++;
	else if (k >= 0)
		(*x) += 2;
	else if (k == -1)
		while (str[*x] && ft_check_t(str + *x, charset) == -1)
			(*x)++;
	t = malloc(*x - i + 1);
	if (!t)
		return (NULL);
	y = 0;
	while (i + y < *x)
	{
		t[y] = str[i + y];
		y++;
	}
	t[y] = '\0';
	return (t);
}

char	**ft_split3(char const *str)
{
	int		i;
	int		x;
	int		s;
	char	**t;
	char	**charset;

	charset = ft_set_charset();
	if (!charset)
		return (NULL);
	i = 0;
	x = 0;
	s = ft_count(str, charset);
	t = malloc(sizeof(char *) * (s + 1));
	if (!t)
		return (NULL);
	while (i < s)
	{
		t[i] = ft_copy(str, charset, &x);
		if (!t[i])
			return (ft_free(charset), ft_free(t), NULL);
		i++;
	}
	t[i] = NULL;
	return (free(charset), t);
}
