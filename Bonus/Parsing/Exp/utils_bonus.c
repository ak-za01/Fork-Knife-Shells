/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 07:59:14 by noctis            #+#    #+#             */
/*   Updated: 2025/06/27 21:27:49 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

int	ft_check_dollar(char *t)
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

int	ft_check_q_status(char *t)
{
	int	i;

	if (!t)
		return (0);
	if (t[0] == '\"')
		i = 2;
	else if (t[0] == '\'')
		i = 1;
	else
		i = 0;
	return (i);
}

int	ft_strlen_2(char **t)
{
	int	s;

	if (!t)
		return (0);
	s = 0;
	while (t[s])
		s++;
	return (s);
}

int	ft_strlen_3(char *t)
{
	int	s;

	if (!t)
		return (0);
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
