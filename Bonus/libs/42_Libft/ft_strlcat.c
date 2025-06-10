/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:25:51 by aakritah          #+#    #+#             */
/*   Updated: 2024/11/01 21:28:06 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s1;
	size_t	s2;

	s1 = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (s1);
	s2 = ft_strlen(dst);
	if (dstsize <= s2)
		return (dstsize + s1);
	i = 0;
	while (src[i] && s2 + i < dstsize - 1)
	{
		dst[s2 + i] = src[i];
		i++;
	}
	dst[s2 + i] = '\0';
	return (s1 + s2);
}
