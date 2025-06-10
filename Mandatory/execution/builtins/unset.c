/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:05:15 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/22 12:12:56 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	remove_variable(char *arg, t_env *env_list)
{
	t_env	*current;
	t_env	*prev; 

	if (!env_list)
		return (1);
	current = env_list;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->name, arg))
		{
			if (prev)
				prev->next = current->next;
			else
				env_list = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

int	ft_unset(t_token *data, t_extra x)
{
	int	i;

	i = 1;
	if (!data->c_arg[i])
		return ((x.exit_status = 1));
	while (data->c_arg[i])
	{
		if (remove_variable(data->c_arg[i], x.env_list))
		{
			error_message("unset", data->c_arg[i]);
			return ((x.exit_status = 1));
		}
		i++;
	}
	return ((x.exit_status = 0));
}
