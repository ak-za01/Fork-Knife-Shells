/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:41:31 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/28 18:16:16 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	is_numeric_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	check_overflow(long long result, int digit, int sign)
{
	unsigned long long	abs_min;

	if (sign == 1 && result > (LLONG_MAX - digit) / 10)
		return (1);
	else
	{
		abs_min = (unsigned long long)LLONG_MAX + 1;
		if ((unsigned long long)result > abs_min / 10)
			return (1);
		if ((unsigned long long)result == abs_min / 10 
			&& (unsigned long long)digit > abs_min % 10)
			return (1);
	}
	return (0);
}

static int	str_to_exit_code(char *str, int *exit_code)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_overflow(result, str[i] - '0', sign))
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	result *= sign;
	*exit_code = (result % 256 + 256) % 256;
	return (1);
}

static int	handle_exit_arg(char *arg, int *exit_code)
{
	char	**split;
	int		is_valid;

	split = ft_split(arg, ' ');
	if (!split)
		return (0);
	if (!split[0] || split[1])
	{
		ft_free(split);
		return (0);
	}
	is_valid = is_numeric_arg(split[0])
		&& str_to_exit_code(split[0], exit_code);
	ft_free(split);
	return (is_valid);
}

int	ft_exit(t_token *data, t_extra *x)
{
	ft_putstr_fd("exit\n", 1);
	if (!data->c_arg[1])
		exit(x->exit_status);
	if (!handle_exit_arg(data->c_arg[1], &x->exit_status))
	{
		ft_putstr_fd("Minishell: line: exit: ", 2);
		ft_putstr_fd(data->c_arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (data->c_arg[2])
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit(x->exit_status);
	return (SUCCESS);
}
