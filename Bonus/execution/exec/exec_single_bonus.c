/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:13:15 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/26 21:19:32 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

int	exec_builtin(t_token *data, t_extra *x)
{
	if (!data->value || !data->value[0])
		return (ERROR);
	if (strcmp(data->value, "echo") == 0)
		return (ft_echo(data));
	else if (strcmp(data->value, "cd") == 0)
		return (ft_cd(data->c_arg, x));
	if (strcmp(data->value, "pwd") == 0)
		return (ft_pwd());
	else if (strcmp(data->value, "export") == 0)
		return (ft_export(data, x));
	else if (strcmp(data->value, "unset") == 0)
		return (ft_unset(data, &x));
	else if (strcmp(data->value, "env") == 0)
		return (ft_env(data, x));
	else if (strcmp(data->value, "exit") == 0)
		return (ft_exit(data, x));
	return (ERROR);
}

int	exec_single(t_token *data, t_extra *x)
{
	if (setup_redirections(data, x) != 0)
	{
		restore_std_fds(x);
		return ((x->exit_status = 1));
	}
	x->exit_status = exec_builtin(data, x);
	if (restore_std_fds(x) != 0)
		return ((x->exit_status = ERROR));
	return (x->exit_status);
}
