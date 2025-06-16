/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:02:27 by aakritah          #+#    #+#             */
/*   Updated: 2024/11/01 20:30:14 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	s1;
	char	*t;

	i = 0;
	s1 = ft_strlen(s);
	t = NULL;
	while (i < s1 + 1)
	{
		if (s[i] == (char)c)
			t = (char *)(s + i);
		i++;
	}
	return (t);
}
