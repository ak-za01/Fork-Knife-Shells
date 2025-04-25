/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:01:40 by anktiri           #+#    #+#             */
/*   Updated: 2025/04/24 19:30:18 by anktiri          ###   ########.fr       */
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
		temp = ft_split(*env, '=');
		if (!temp)
			return ((free(new_node)), NULL);
		new_node->name = temp[0];
		new_node->value = temp[1];
		new_node->next = NULL;
		if (!env_list)
			env_list = new_node;
		else
			current->next = new_node;
		current = new_node;
		env++;
	}
	return (env_list);
}

int is_builtin(char *cmd)
{
    if (!cmd)
        return 0;
    if (strcmp(cmd, "echo") == 0 ||
        strcmp(cmd, "cd") == 0 ||
        strcmp(cmd, "pwd") == 0 ||
        strcmp(cmd, "export") == 0 ||
        strcmp(cmd, "unset") == 0 ||
        strcmp(cmd, "env") == 0 ||
        strcmp(cmd, "exit") == 0)
        return 1;
    return 0;
}

int exec_builtin(char **args, t_env **env_list)
{
    if (!args || !args[0])
        return (ERROR);

    if (strcmp(args[0], "echo") == 0)
        return ft_echo(args);
    // else if (strcmp(args[0], "cd") == 0)
    //     return ft_cd(args, *env_list);
    if (strcmp(args[0], "pwd") == 0)
        return ft_pwd();
    // else if (strcmp(args[0], "export") == 0)
    //     return ft_export(args, env_list);
    // else if (strcmp(args[0], "unset") == 0)
    //     return ft_unset(args, env_list);
    else if (strcmp(args[0], "env") == 0)
        return ft_env(*env_list);
    else if (strcmp(args[0], "exit") == 0)
        return ft_exit(args);
    return (ERROR);
}

int ft_env(t_env *env_list)
{
	t_env	*current;

	if (!env_list)
		return (SUCCESS);
	current = env_list;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (SUCCESS);
}

int ft_exit(char **args)
{
	int exit_code;

	if (args[1])
	{
		exit_code = atoi(args[1]);
		if (exit_code < 0)
			exit_code = 0;
	}
	else
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

int	ft_echo(char **args)
{
	int i = 1;
	int newline = 1;

	if (!args || !args[1])
	{
		printf("\n");
		return (SUCCESS);
	}
	while (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		newline = 0;
		printf("enter");
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
