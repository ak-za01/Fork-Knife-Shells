/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:01:40 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/02 15:58:14 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int exec_builtin(t_token *data)
{
    if (!data->value || !data->value[0])
        return (ERROR);

    if (strcmp(data->value, "echo") == 0)
        return ft_echo(data);
    // else if (strcmp(data->value, "cd") == 0)
    //     return ft_cd(data, *env_list);
    if (strcmp(data->value, "pwd") == 0)
        return ft_pwd();
    else if (strcmp(data->value, "export") == 0)
        return ft_export(data);
    // else if (strcmp(data->value, "unset") == 0)
    //     return ft_unset(data, env_list);
    else if (strcmp(data->value, "env") == 0)
        return ft_env(data);
    else if (strcmp(data->value, "exit") == 0)
        return ft_exit(data);
    return (ERROR);
}

int ft_exit(t_token *data)
{
    int exit_code = 0;
    if (data->c_arg[1])
        exit_code = ft_atoi(data->c_arg[1]) % 256;
    if (exit_code < 0)
        exit_code = 0;
    printf("exit\n");
    exit(exit_code);
    return (SUCCESS);
}

int	ft_pwd(void)
{
	char cwd[1024];

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
