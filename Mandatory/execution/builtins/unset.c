/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:05:15 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/24 00:56:21 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	remove_variable(char *arg, t_env **env_list)
{
	t_env	*current;
	t_env	*prev;

	if (!env_list || !*env_list)
		return (1);
	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->name, arg))
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->name);
			free(current->value);
			return (free(current), 0);
		}
		prev = current;
		current = current->next;
	}
	if (!var_exist(*env_list, arg))
		return (2);
	return (1);
}

int	valid_variable2(char *str)
{
	int	i;
	int	valid;

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
		while (str[i])
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

int	ft_unset(t_token *data, t_extra **x)
{
	int	i;
	int	f;

	i = 1;
	f = 0;
	if (!data->c_arg[i])
		return (((*x)->exit_status = 0));
	while (data->c_arg[i])
	{
		if (!valid_variable2(data->c_arg[i]))
		{
			error_message("unset", data->c_arg[i]);
			f = 1;
		}
		if (remove_variable(data->c_arg[i], &(*x)->env_list) == 1)
		{
			error_message("unset", data->c_arg[i]);
			f = 1;
		}
		i++;
	}
	if (f)
		return ((*x)->exit_status = 1);
	return (((*x)->exit_status = 0));
}
