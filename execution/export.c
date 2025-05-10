/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:50:37 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/09 21:13:08 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

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

char	*remove_quotes(char *str)
{
	int		len;
	char	*result;
	
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2)
	{
		if ((str[0] == '"' && str[len - 1] == '"') || 
			(str[0] == '\'' && str[len - 1] == '\''))
		{
			result = ft_strndup(str + 1, len - 2);
			return (result);
		}
	}
	return (ft_strdup(str));
}

int	valid_variable(char *str)
{
	int		i;
	char	*clean_str;
	int		valid;

	clean_str = remove_quotes(str);
	if (!clean_str)
		return (0);
	i = 0;
	valid = 1;
	if (!clean_str[i])
		valid = 0;
	else if (ft_isdigit(clean_str[0]))
		valid = 0;
	else
	{
		while (clean_str[i] && clean_str[i] != '=')
		{
			if (!ft_isalnum(clean_str[i]) && clean_str[i] != '_')
			{
				valid = 0;
				break;
			}
			i++;
		}
	}
	free(clean_str);
	return (valid);
}

void	error_message(char *cmd, char *str)
{
	char	*clean_str;

	clean_str = remove_quotes(str);
	if (clean_str)
	{
		fprintf(stderr, "minishell: %s: `%s': not a valid identifier\n", 
				cmd, clean_str);
		free(clean_str);
	}
	else
		fprintf(stderr, "minishell: %s: invalid argument\n", cmd);
}

int	search_variable(t_env **current, char *str)
{
	t_env	*temp;
	int		i;
	char	*var_name;
	char	*clean_str;

	clean_str = remove_quotes(str);
	if (!clean_str)
		return (0);
	i = 0;
	temp = *current;
	while (clean_str[i] && clean_str[i] != '=')
		i++;
	var_name = ft_strndup(clean_str, i);
	free(clean_str);
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
	char	*clean_str;

	clean_str = remove_quotes(str);
	if (!clean_str)
		return (NULL);
	value = ft_split_env(clean_str, '=');
	free(clean_str);
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
	char	*clean_arg;

	current = env_list;
	clean_arg = remove_quotes(arg);
	if (!clean_arg)
		return (NULL);
	value = ft_split_env(clean_arg, '=');
	free(clean_arg);
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
	char	*clean_arg;

	clean_arg = remove_quotes(arg);
	if (!clean_arg)
		return (1);
	if (!ft_strchr(clean_arg, '='))
	{
		free(clean_arg);
		return (0);
	}
	new_val = get_var_value(arg);
	free(clean_arg);
	if (!new_val)
		return (1);
	if (current->value)
		free(current->value);
	current->value = new_val;
	return (0);
}

static int	process_export_arg(t_token *data, char *arg)
{
	t_env	*current;
	char	*clean_arg;

	if (!valid_variable(arg))
	{
		error_message("export", arg);
		return (1);
	}
	current = data->env_list;
	if (search_variable(&current, arg))
		return (process_existing_var(current, arg));
	else
	{
		clean_arg = remove_quotes(arg);
		if (!clean_arg)
			return (1);
		if (ft_strchr(clean_arg, '='))
		{
			free(clean_arg);
			if (!add_new_node(arg, data->env_list))
				return (1);
		}
		else
			free(clean_arg);
	}
	return (0);
}

int	ft_export(t_token *data)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (!data->c_arg[i])
		return (0);
	while (data->c_arg[i])
	{
		if (process_export_arg(data, data->c_arg[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
