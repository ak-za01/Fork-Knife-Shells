/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:37:10 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/04 13:47:04 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

static long	ft_count(char const *s, char c)
{
	long	i;
	long	f;
	long	i_c;
	char	q;
	long	count;

	i = 0;
	f = 0;
	i_c = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && i_c == 0)
			(q = s[i], i_c = !i_c);
		else if (i_c == 1 && s[i] == q)
			i_c = !i_c;
		if (s[i] != c && f == 0 && i_c == 0)
			(count++, f = 1);
		else if (s[i] == c)
			f = 0;
		i++;
	}
	if (i_c == 1)
		return (-1);
	return (count);
}

static void	ft_filter(const char *s, char c, long *i)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
}

static char	*ft_copy(const char *s, char c, long *i)
{
	long	j;
	long	k;
	long	i_c;
	char	q;
	char	*t;

	i_c = 0;
	k = 0;
	j = *i;
	while (s[j] && (s[j] != c || i_c == 1))
	{
		if ((s[j] == '\'' || s[j] == '\"') && i_c == 0)
			(q = s[j], i_c = !i_c);
		else if (i_c == 1 && s[j] == q)
			i_c = !i_c;
		j++;
	}
	t = malloc((j - *i + 1) * 1);
	if (!t)
		return (NULL);
	while (*i < j)
		(t[k++] = s[*i], (*i)++);
	t[k] = '\0';
	return (t);
}

char	**ft_split2(char const *s, char c)
{
	long	i;
	long	k;
	char	**t;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	if ((ft_count(s, c) + 1) == -1)
		return (perror("Error split2.c : 90"), NULL);
	t = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	while (k < ft_count(s, c))
	{
		ft_filter(s, c, &i);
		t[k] = ft_copy(s, c, &i);
		if (!t[k])
			return (ft_free(t), NULL);
		k++;
	}
	t[k] = NULL;
	return (t);
}
