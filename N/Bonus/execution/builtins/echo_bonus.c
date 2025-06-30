/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 07:32:22 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/28 20:17:13 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

int	is_n_flag(char *str)
{
	if (!str || str[0] != '-')
		return (0);
	str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	ft_echo(t_token *data)
{
	int	first_arg;
	int	newline;
	int	i;

	first_arg = 1;
	newline = 1;
	i = 1;
	if (!data || !data->c_arg || !data->c_arg[0])
		return ((ft_putstr_fd("\n", 1)), 0);
	while (data->c_arg[i] && is_n_flag(data->c_arg[i]))
		newline = ((i++), 0);
	while (data->c_arg[i])
	{
		if (!first_arg)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(data->c_arg[i], 1);
		first_arg = 0;
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
