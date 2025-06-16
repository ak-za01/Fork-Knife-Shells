/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:33:12 by aakritah          #+#    #+#             */
/*   Updated: 2024/11/01 19:08:32 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_check1(char a, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == a)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_creat(const char *str, size_t i, size_t j)
{
	char	*t;
	size_t	k;

	k = 0;
	t = malloc((j - (i - 1) + 1) * 1);
	if (!t)
		return (NULL);
	while (i <= j)
	{
		t[k] = str[i];
		i++;
		k++;
	}
	t[k] = '\0';
	return (t);
}

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	i;
	size_t	j;

	if (!str || !set)
		return (NULL);
	if (str[0] == '\0')
		return (ft_strdup(""));
	i = 0;
	while (str[i])
	{
		if (ft_check1(str[i], set) == 0)
			break ;
		i++;
	}
	j = ft_strlen(str) - 1;
	while (j > i)
	{
		if (ft_check1(str[j], set) == 0)
			break ;
		j--;
	}
	return (ft_creat(str, i, j));
}
