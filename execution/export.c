/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:50:37 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/11 22:45:30 by anktiri          ###   ########.fr       */
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
	int		i;
	int		valid;
	
	i = 0;
	valid = 1;
	if (!str[i])
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
				break;
			}
			i++;
		}
	}
	return (valid);
}

void	error_message(char *cmd, char *str)
{
	char	*clean_str = NULL;

	// clean_str = remove_quotes(str);
	// later add a flag to detect if there are quotes
	if (!clean_str)
	{
		fprintf(stderr, "minishell: %s: `%s': not a valid identifier\n", 
				cmd, str);
	}
	else
		fprintf(stderr, "minishell: %s: invalid argument\n", cmd);
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
		if (!ft_strncmp(temp->name, var_name, ft_strlen(var_name) + 1))
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

char	*get_var_value(char *str)
{
	char	**value;
	char	*result;
	
	value = ft_split_env(str, '=');
	if (!value)
		return (NULL);
	result = value[1];
	free(value[0]);
	free(value);
	return (result);
}

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
	new_node->next = NULL;
	while (current && current->next)
		current = current->next;
	current->next = new_node;
	free(value);
	return (env_list);
}

static int	process_existing_var(t_env *current, char *arg)
{
	char	*new_val;
	
	if (!ft_strchr(arg, '='))
		return (0);
	new_val = get_var_value(arg);
	if (!new_val)
		return (1);
	if (current->value)
		free(current->value);
	current->value = new_val;
	return (0);
}

static int	process_export_arg(char *arg, t_env *env_list)
{
	t_env	*current;

	if (!valid_variable(arg))
	{
		error_message("export", arg);
		return (1);
	}
	current = env_list;
	if (search_variable(&current, arg))
		return (process_existing_var(current, arg));
	else
	{
		if (!add_new_node(arg, env_list))
			return (1);
	}
	return (0);
}

int	ft_export(t_token *data, t_extra x)
{
	int		i;

	i = 1;
	if (!data->c_arg[i])
		return (0);
	while (data->c_arg[i])
	{
		if (process_export_arg(data->c_arg[i], x.env_list))
			x.exit_status = 1;
		i++;
	}
	return (x.exit_status);
}
