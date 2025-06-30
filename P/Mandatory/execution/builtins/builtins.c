/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:01:40 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/21 11:39:14 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	exec_builtin(t_token *data, t_extra x)
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
		return (ft_unset(data, x));
	else if (strcmp(data->value, "env") == 0)
		return (ft_env(data, x));
	else if (strcmp(data->value, "exit") == 0)
		return (ft_exit(data, x));
	return (ERROR);
}

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (SUCCESS);
	}
	else
	{
		perror("getcwd() error");
		return (ERROR);
	}
}
