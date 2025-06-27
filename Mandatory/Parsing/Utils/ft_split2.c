/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:37:10 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/21 20:39:01 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

char	**ft_split2(char const *s)
{
	long	i;
	long	k;
	char	**t;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	if ((ft_count_split2(s)) == -1)
		return (NULL);
	t = malloc((ft_count_split2(s) + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	while (k < ft_count_split2(s))
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		t[k] = ft_copy_split2(s, &i);
		if (!t[k])
			return (ft_free(t), NULL);
		k++;
	}
	t[k] = NULL;
	return (t);
}

long	ft_count_split2(char const *s)
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
			ft_fix_norminet_1(&q, s + i, &i_c);
		else if (i_c == 1 && s[i] == q)
			i_c = !i_c;
		if (ft_isspace(s[i]) == 0 && f == 0 && i_c == 0)
			ft_fix_norminet_2(&f, &count);
		else if (ft_isspace(s[i]))
			f = 0;
		i++;
	}
	if (i_c == 1)
		return (-1);
	return (count);
}

char	*ft_copy_split2(const char *s, long *i)
{
	long	j;
	long	k;
	long	i_c;
	char	q;
	char	*t;

	i_c = 0;
	k = 0;
	j = *i;
	while (s[j] && (ft_isspace(s[j]) == 0 || i_c == 1))
	{
		if ((s[j] == '\'' || s[j] == '\"') && i_c == 0)
			ft_fix_norminet_1(&q, s + j, &i_c);
		else if (i_c == 1 && s[j] == q)
			i_c = !i_c;
		j++;
	}
	t = malloc((j - *i + 1) * 1);
	if (!t)
		return (NULL);
	while (*i < j)
		t[k++] = s[(*i)++];
	t[k] = '\0';
	return (t);
}

void	ft_fix_norminet_1(char *a, char const *b, long *n1)
{
	*a = *b;
	(*n1) = !(*n1);
}

void	ft_fix_norminet_2(long *n2, long *n1)
{
	(*n1)++;
	(*n2)++;
}
