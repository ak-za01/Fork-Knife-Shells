/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:29:26 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/08 11:31:07 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

char	**ft_split4(char const *str)
{
	int		i;
	int		s;
	int		k;
	char	**t;

	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	s = ft_count_split4(str);
	t = malloc((s + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	while (i < s)
	{
		t[i] = ft_copy_split4(str, &k);
		if (!t[i])
			return (ft_free(t), NULL);
		i++;
	}
	t[i] = NULL;
	return (t);
}

int	ft_count_split4(char const *s)
{
	int		i;
	int		count;
	char	q_c;

	i = 0;
	count = 0;
	q_c = 0;
	while (s[i])
	{
		count++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			q_c = s[i++];
			while (s[i] && s[i] != q_c)
				i++;
			i++;
		}
		else
		{
			while (s[i] && !(s[i] == '\'' || s[i] == '\"'))
				i++;
		}
	}
	return (count);
}

char	*ft_copy_split4(char const *s, int *k)
{
	int		i;
	int		j;
	char	*t;
	char	q_c;

	i = (*k);
	if (s[*k] == '\'' || s[*k] == '\"')
	{
		q_c = s[(*k)++];
		while (s[*k] && s[*k] != q_c)
			(*k)++;
		(*k)++;
	}
	else
		while (s[*k] && !(s[*k] == '\'' || s[*k] == '\"'))
			(*k)++;
	t = malloc((((*k) - i + 1) + 1));
	if (!t)
		return (NULL);
	j = 0;
	while (i < *k)
		t[j++] = s[i++];
	t[j] = '\0';
	return (t);
}
