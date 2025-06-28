/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:33:08 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/28 17:52:35 by anktiri          ###   ########.fr       */
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
	if (ft_strcmp(temp[0], "OLDPWD") == 0)
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

void	shellvl_error(int new_value)
{
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putstr_fd(ft_itoa(new_value), 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
}
