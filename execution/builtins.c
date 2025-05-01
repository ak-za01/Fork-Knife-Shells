/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:01:40 by anktiri           #+#    #+#             */
/*   Updated: 2025/04/30 18:53:50 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"


t_env	*create_env_list(char **env)
{
	t_env	*env_list;
	t_env	*current;
	t_env	*new_node;
	char	**temp;

	env_list = ((current = NULL), NULL);
	while (*env)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		temp = ft_split_env(*env, '=');
		if (!temp)
			return ((free(new_node)), NULL);
		new_node->name = temp[0];
		new_node->value = temp[1];
		new_node->next = NULL;
		free(temp);
		if (!env_list)
			env_list = new_node;
		else
			current->next = new_node;
		current = new_node;
		env++;
	}
	return (env_list);
}


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
    // else if (strcmp(data->value, "export") == 0)
    //     return ft_export(data, env_list);
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
