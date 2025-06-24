/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:53:28 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/24 01:10:22 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

t_env	*create_env_node(char *env_str)
{
	t_env	*new_node;
	char	**temp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	temp = ft_split_env(env_str, '=');
	if (!temp)
	{
		free(new_node);
		return (NULL);
	}
	new_node->name = temp[0];
	if (strcmp(temp[0], "OLDPWD") == 0)
	{
		new_node->value = NULL;
		free(temp[1]);
	}
	else
		new_node->value = temp[1];
	new_node->next = NULL;
	free(temp);
	return (new_node);
}

t_env	*create_env_list(char **env)
{
	t_env	*env_list;
	t_env	*current;
	t_env	*new_node;

	env_list = NULL;
	current = NULL;
	while (*env)
	{
		new_node = create_env_node(*env);
		if (!new_node)
			return (NULL);
		if (!env_list)
			env_list = new_node;
		else
			current->next = new_node;
		current = new_node;
		env++;
	}
	return (env_list);
}

int	add(t_env *env_list, char *name, char *value)
{
	if (add_var(env_list, name, value))
	{
		free(env_list->name);
		free(env_list->value);
		free(env_list);
		return (1);
	}
	return (0);
}

t_env	*create_env()
{
	t_env	*env_list;
	char	cwd[1024];

	env_list = malloc(sizeof(t_env));
	if (!env_list)
		return (NULL);
	env_list->name = ft_strdup("OLDPWD");
	env_list->value = NULL;
	env_list->next = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		free(env_list->name);
		free(env_list->value);
		free(env_list);
		return (NULL);
	}
	if (add(env_list, "PWD", cwd))
		return (NULL);
	if (add(env_list, "SHLVL", "0"))
		return (NULL);
	return (env_list);
}

int	ft_env(t_token	*data, t_extra *x)
{
	t_env	*current;

	(void)data;
	if (!x->env_list)
		return (ERROR);
	current = x->env_list;
	while (current)
	{
		if (current->value && current->name)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (SUCCESS);
}

static int	update_var(t_env *env_list, char *name)
{
	t_env	*current;
	int		new_value;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			new_value = ft_atoi(current->value);
			new_value++;
			free(current->value);
			current->value = ft_itoa(new_value);
			if (!current->value)
				return (1);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

void	init_extra(t_extra *x, char **env)
{
	if (env && *env)
		x->env_list = create_env_list(env);
	else
	{
		x->env_list = create_env();
		printf("env is null\n");
	}
	if (!var_exist(x->env_list, "OLDPWD"))
	{
		if (add_var(x->env_list, "OLDPWD", NULL))
			return ;
	}
	if (!var_exist(x->env_list, "SHLVL"))
	{
		if (add_var(x->env_list, "SHLVL", "1"))
			return ;
	}
	else
	{
		if (update_var(x->env_list, "SHLVL"))
			return ;
	}
	x->exit_status = 0;
}
