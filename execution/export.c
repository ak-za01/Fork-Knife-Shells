/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:50:37 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/06 21:46:19 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	i;
	char	*result;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	valid_variable(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (i == 0 && ft_isdigit(str[i]))
			return (0);
		if ((!ft_isalnum(*str) && *str != '_'))
			return (0);
		i++;
	}
	return (1);
}

void	error_message(char *cmd, char *str)
{
	if (str)
		fprintf(stderr, "minishell: %s: `%s': not a valid identifier\n", cmd, str);
	else
		return ;
}

int	search_variable(t_env **current, char *str)
{
	t_env	*temp;
	int		i;
	char	*var_name;

	i = 0;
	temp = *current;
	while (str[i] && str[i] != '=')
		i++;
	var_name = ft_strndup(str, i);
	if (!var_name)
		return (0);
	while (temp)
	{
		if (!ft_strncmp(temp->name, var_name, ft_strlen(var_name)))
		{
			free(var_name);
			*current = temp;
			return (1);
		}
		temp = temp->next;
	}
	free(var_name);
	return (0);
}

char	*new_value(char *str)
{
	char	**value;

	value = ft_split_env(str, '=');
	if (!value)
		return (NULL);
	free (value[0]);
	free (value);
	return (value[1]);
}

t_env	*new_env_node(char *arg, t_env *env_list)
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
	while (current->next)
		current = current->next;
	new_node->name = value[0];
	new_node->value = value[1];
	new_node->next = NULL;
	current->next = new_node;
	free (value);
	return (env_list);
}

int ft_export(t_token *data)
{
	t_env	*current;
	int		i;
	int		ret;

	i = ((ret = 0), 1);
	while (data->c_arg[i])
	{
		if (!valid_variable(data->c_arg[i]))
		{
			error_message("export", data->c_arg[i]);
			ret = 1;
			i++;
			continue;
		}
		current = data->env_list;
		if (search_variable(&current, data->c_arg[i]))
		{
			free (current->value);
			current->value = new_value(data->c_arg[i]);
			if (!current->value)
				return (1);
		}
		else
		{
			if (!ft_strchr(data->c_arg[i], '='))
				continue ;
			else
				current = new_env_node(data->c_arg[i], data->env_list);
		}
		i++;
	}
	return (0);
}
