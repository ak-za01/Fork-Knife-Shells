/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:53:28 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/11 22:44:17 by anktiri          ###   ########.fr       */
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
		if (!env_list)
			env_list = new_node;
		else
			current->next = new_node;
		current = new_node;
		((free(temp)), env++);
	}
	return (env_list);
}

int	ft_env(t_token	*data, t_extra x)
{
	t_env	*current;

	if (!x.env_list || data->c_arg[1])
		return (SUCCESS);
	current = x.env_list;
	while (current)
	{
		if (current->value && current->name)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (SUCCESS);
}
