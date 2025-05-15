/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 07:59:14 by noctis            #+#    #+#             */
/*   Updated: 2025/05/12 17:39:31 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_check(char *t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		if (t[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen_2(char **t)
{
	int	s;

	s = 0;
	while (t[s])
		s++;
	return (s);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
