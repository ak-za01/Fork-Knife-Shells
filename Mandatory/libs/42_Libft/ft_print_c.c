/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 21:52:44 by aakritah          #+#    #+#             */
/*   Updated: 2025/02/08 19:00:51 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_c(char c, va_list ptr)
{
	if (c == '%')
	{
		ft_putchar('%');
		return (1);
	}
	ft_putchar(va_arg(ptr, int));
	return (1);
}
