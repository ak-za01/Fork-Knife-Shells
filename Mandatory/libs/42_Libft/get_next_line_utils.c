/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:30:38 by aakritah          #+#    #+#             */
/*   Updated: 2025/02/08 18:53:41 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*t;
	int		s;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup2(s2));
	s = ft_strlen(s1) + ft_strlen(s2);
	t = malloc(s + 1);
	if (!t)
		return (free(s1), s1 = NULL, free(s2), s2 = NULL, NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		t[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		t[i++] = s2[j++];
	t[i] = '\0';
	return (free(s1), s1 = NULL, t);
}

char	*ft_strdup2(const char *s1)
{
	size_t	i;
	size_t	s;
	char	*t;

	if (!s1)
		return (NULL);
	s = ft_strlen(s1);
	t = malloc((s + 1) * 1);
	if (!t)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		t[i] = s1[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}

char	*ft_strchr2(const char *s, int c)
{
	size_t	s1;
	size_t	i;

	if (!s)
		return (NULL);
	s1 = ft_strlen(s);
	i = 0;
	while (i < s1 + 1)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
