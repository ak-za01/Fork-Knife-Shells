/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 07:32:22 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/21 11:39:22 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

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
		return ((printf("\n")), 0);
	while (data->c_arg[i] && is_n_flag(data->c_arg[i]))
		newline = ((i++), 0);
	while (data->c_arg[i])
	{
		if (!first_arg)
			printf(" ");
		printf("%s", data->c_arg[i]);
		first_arg = 0;
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
