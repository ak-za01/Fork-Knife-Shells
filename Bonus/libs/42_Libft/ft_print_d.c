/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:16:49 by aakritah          #+#    #+#             */
/*   Updated: 2025/02/08 19:01:11 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count1(int n)
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

static int	ft_putnbr2(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_putnbr2(n / 10);
	ft_putchar((n % 10) + '0');
	count++;
	return (count);
}

int	ft_print_d(char n, va_list ptr)
{
	int	i;

	if (n == 'u')
		return (ft_putnbr2(va_arg(ptr, unsigned int)));
	i = va_arg(ptr, int);
	ft_putnbr(i);
	return (ft_count1(i));
}
