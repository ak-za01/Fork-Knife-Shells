/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:48:25 by aakritah          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:13 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	s1;

	i = 0;
	s1 = ft_strlen(needle);
	if (!haystack && len == 0)
		return (NULL);
	if (s1 == 0)
		return ((char *)haystack);
	while (haystack[i] && i + s1 <= len)
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(haystack + i, needle, s1) == 0)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
