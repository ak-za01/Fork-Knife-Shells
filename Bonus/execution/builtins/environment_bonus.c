/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:53:28 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/16 21:29:57 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

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
		new_node->original = ((new_node->next = NULL), 1);
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

	(void)data;
	if (!x.env_list)
		return (ERROR);
	current = x.env_list;
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
	x->env_list = create_env_list(env);
	x->exit_status = 0;
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
}
