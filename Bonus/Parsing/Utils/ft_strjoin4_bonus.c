/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin4_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:48:07 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/16 21:32:04 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

char	*ft_strjoin4(char **s1)
{
	char	*t;
	int		s;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	i = 0;
	s = 0;
	while (s1[i])
		s += ft_strlen(s1[i++]);
	t = malloc(s + 1);
	if (!t)
		return (NULL);
	i = 0;
	s = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i][j])
			t[s++] = s1[i][j++];
		i++;
	}
	t[s] = '\0';
	return (t);
}
