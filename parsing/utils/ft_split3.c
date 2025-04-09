/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:45:20 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/09 21:21:23 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

static char	**ft_set_charset(void)
{
	char	**charset;

	charset = malloc(sizeof(char *) * 6);
	if (!charset)
		return (NULL);
	charset[0] = ">>";
	charset[1] = "<<";
	charset[2] = ">";
	charset[3] = "<";
	charset[4] = "|";
	charset[5] = NULL;
	return (charset);
}
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
	int	x;
	int	copy;
	int	k;
	int	f;

	x = 0;
	copy = 0;
	k = 0;
	f = 0;
	while (str[x])
	{
		k = ft_check_t(str + x, charset);
		if (k == -1)
		{
			if (f == 0)
			{
				copy++;
				f = 1;
				x++;
			}
			else
			{
				x++;
			}
		}
		else
		{
			copy++;
			f = 0;
			if (k < 2)
			{
				x += 2;
			}
			else
			{
				x++;
			}
		}
	}
	return (copy);
}

static char	*ft_copy(char const *str, char **charset, int *x)
{
	int		s;
	int		i;
	int		y;
	int		k;
	char	*t;

	t = NULL;
	k = ft_check_t(str + *x, charset);
	i = *x;
	y = 0;
	if (k < 0)
	{
		while (str[*x])
		{
			k = ft_check_t(str + *x, charset);
			if (k >= 0)
			{
				s = *x - i + 1;
				t = malloc(sizeof(char) * s);
				if (!t)
					return (NULL);
				while (i + y < *x)
				{
					t[y] = str[i + y];
					y++;
				}
				t[y] = '\0';
				break ;
			}
			(*x)++;
		}
		if (str[*x] == '\0')
		{
			s = *x - i + 1;
			t = malloc(sizeof(char) * s);
			if (!t)
				return (NULL);
			while (i + y < *x)
			{
				t[y] = str[i + y];
				y++;
			}
			t[y] = '\0';
		}
	}
	else
	{
		if (k < 2)
		{
			(*x) += 2;
			s = *x - i + 1;
			t = malloc(sizeof(char) * s);
			if (!t)
				return (NULL);
			y = 0;
			while (i + y < *x)
			{
				t[y] = str[i + y];
				y++;
			}
			t[y] = '\0';
		}
		else
		{
			(*x) += 1;
			s = *x - i + 1;
			t = malloc(sizeof(char) * s);
			if (!t)
				return (NULL);
			while (i + y < *x)
			{
				t[y] = str[i + y];
				y++;
			}
			t[y] = '\0';
		}
	}
	return (t);
}
char	**ft_split3(char const *str)
{
	int		i;
	int		x;
	int		y;
	int		k;
	int		f;
	char	**result;
	char	**charset;
	int		s;
	char	**t;

	charset = ft_set_charset();
	if (!charset)
		return (NULL);
	i = 0;
	x = 0;
	f = 0;
	s = ft_count(str, charset);
	t = malloc(sizeof(char *) * (s + 1));
	if (!t)
		return (NULL);
	while (i < s)
	{
		t[i] = ft_copy(str, charset, &x);
		if (!t[i])
			return (NULL); // free t
		i++;
	}
	t[i] = NULL;
	free(charset);
	return (t);
}
