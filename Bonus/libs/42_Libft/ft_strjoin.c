/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:51:14 by aakritah          #+#    #+#             */
/*   Updated: 2024/11/01 18:07:37 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	n1;
	size_t	n2;
	char	*dst;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	dst = malloc((n1 + n2 + 1) * 1);
	if (!dst)
		return (NULL);
	if (ft_strlcpy(dst, s1, (n1 + n2 + 1)) == n1)
		if (ft_strlcat(dst, s2, (n1 + n2 + 1)) == n1 + n2)
			return (dst);
	return (NULL);
}
