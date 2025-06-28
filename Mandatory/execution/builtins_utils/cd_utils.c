/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:26:23 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/27 22:31:08 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	var_exist(t_env *env_list, char *name)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	add_var(t_env *env_list, char *name, char *value)
{
	t_env	*new_var;
	t_env	*current;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (1);
	new_var->name = ft_strdup(name);
	if (!new_var->name)
		return ((free(new_var)), 1);
	if (!value)
		new_var->value = value;
	else
	{
		new_var->value = ft_strdup(value);
		if (!new_var->value)
			return (free(new_var->name), free(new_var), 1);
	}
	new_var->next = NULL;
	if (!env_list)
		return ((free(new_var->name), free(new_var->value), free(new_var)), 1);
	current = env_list;
	while (current->next)
		current = current->next;
	current->next = new_var;
	return (0);
}

static int	update_var(t_env *env_list, char *name, char *dir)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(dir);
			if (!current->value)
				return (1);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	get_var(t_env *env_list, char *name, char *value)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			value = current->value;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	update_pwd(t_extra *x, char *old_dir)
{
	char	current[PATH_MAX];

	if (!getcwd(current, PATH_MAX) && !get_var(x->env_list, "PWD", current))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		return ((x->exit_status = 1));
	}
	else
	{
		if (update_var(x->env_list, "OLDPWD", old_dir))
			return ((x->exit_status = 1));
	}
	if (update_var(x->env_list, "PWD", current))
		return ((x->exit_status = 1));
	return ((x->exit_status = 0));
}
