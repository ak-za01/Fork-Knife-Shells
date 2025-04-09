/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:09:53 by aakritah          #+#    #+#             */
/*   Updated: 2024/11/02 10:02:26 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy1(unsigned char *ds, const unsigned char *sr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		ds[i] = sr[i];
		i++;
	}
}

static void	ft_copy2(unsigned char *ds, const unsigned char *sr, size_t len)
{
	int	i;

	i = (int)(len - 1);
	while (i >= 0)
	{
		ds[i] = sr[i];
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*ds;
	const unsigned char	*sr;

	sr = (const unsigned char *)src;
	ds = (unsigned char *)dest;
	if (ds == sr)
		return (dest);
	else if (ds < sr)
		ft_copy1(ds, sr, len);
	else if (ds > sr)
		ft_copy2(ds, sr, len);
	return (dest);
}
