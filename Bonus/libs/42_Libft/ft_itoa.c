/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:56:14 by aakritah          #+#    #+#             */
/*   Updated: 2024/11/02 12:08:07 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*t;
	int		s1;
	int		f;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	f = 0;
	s1 = ft_count(n);
	if (n < 0)
	{
		f = 1;
		n *= -1;
	}
	t = malloc(s1 + 1);
	if (!t)
		return (NULL);
	t[s1--] = '\0';
	while (s1 >= 0)
	{
		t[s1--] = n % 10 + '0';
		n = n / 10;
	}
	if (f == 1)
		t[0] = '-';
	return (t);
}
