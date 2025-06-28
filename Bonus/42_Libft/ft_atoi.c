/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:56:37 by aakritah          #+#    #+#             */
/*   Updated: 2024/11/01 20:54:40 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long	r;
	int					f;

	r = 0;
	f = 1;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			f *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		r = r * 10 + (*str - '0');
		if (r > LLONG_MAX && f == 1)
			return (-1);
		if (r > LLONG_MAX && f == -1)
			return (0);
		str++;
	}
	return ((int)(r * f));
}
