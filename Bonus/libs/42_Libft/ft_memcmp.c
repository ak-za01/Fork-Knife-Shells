/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:11:45 by aakritah          #+#    #+#             */
/*   Updated: 2024/11/02 13:17:04 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*t1;
	const unsigned char	*t2;

	i = 0;
	t1 = (const unsigned char *)s1;
	t2 = (const unsigned char *)s2;
	while (i < n && t1[i] == t2[i])
		i++;
	if (i == n)
		return (0);
	return (t1[i] - t2[i]);
}
