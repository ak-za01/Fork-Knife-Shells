/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:49:14 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/16 21:30:07 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

t_env	*add_new_node(char *arg, t_env *env_list)
{
	t_env	*new_node;
	t_env	*current;
	char	**value;

	current = env_list;
	value = ft_split_env(arg, '=');
	if (!value)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(value[0]);
		free(value[1]);
		free(value);
		return (NULL);
	}
	new_node->name = value[0];
	new_node->value = value[1];
	new_node->original = 0;
	new_node->next = NULL;
	while (current && current->next)
		current = current->next;
	current->next = new_node;
	free(value);
	return (env_list);
}

int	search_variable(t_env **current, char *str)
{
	t_env	*temp;
	char	**var_name;

	temp = *current;
	var_name = ft_split_env(str, '=');
	if (!var_name)
		return (0);
	while (temp)
	{
		if (!ft_strncmp(temp->name, var_name[0], ft_strlen(var_name[0]) + 1))
		{
			free(var_name[0]);
			free(var_name[1]);
			free(var_name);
			*current = temp;
			return (1);
		}
		temp = temp->next;
	}
	free(var_name[0]);
	free(var_name[1]);
	free (var_name);
	return (0);
}

int	valid_variable(char *str)
{
	int		i;
	int		valid;

	i = 0;
	valid = 1;
	if (!str[i])
		valid = 0;
	else if (str[i] == '=')
		valid = 0;
	else if (ft_isdigit(str[0]))
		valid = 0;
	else
	{
		while (str[i] && str[i] != '=')
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
			{
				valid = 0;
				break ;
			}
			i++;
		}
	}
	return (valid);
}

void	print_env_list(t_env *list)
{
	t_env	*current;
	t_env	*temp;

	current = list;
	while (current)
	{
		print_env_node(current);
		temp = current;
		current = current->next;
		free_temp_env(temp);
	}
}
