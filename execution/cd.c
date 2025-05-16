/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:27:50 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/16 19:52:13 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

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
	new_var->value = ft_strdup(value);
	if (!new_var->value)
	{
		free(new_var->name);
		free(new_var);
		return (1);
	}
	new_var->original = 1;
	new_var->next = NULL;
	if (!env_list)
		return ((free(new_var->name), free(new_var->value), free(new_var)), 1);
	current = env_list;
	while (current->next)
		current = current->next;
	current->next = new_var;
	return (0);
}

int	update_var(t_env *env_list, char *name, char *dir)
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

static int	update_pwd(t_env *env_list, char *old_dir)
{
	char	current[PATH_MAX];

	if (!getcwd(current, PATH_MAX))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	if (!var_exist(env_list, "OLDPWD"))
	{
		if (add_var(env_list, "OLDPWD", old_dir))
			return (1);
	}
	else 
	{
		if (update_var(env_list, "OLDPWD", old_dir))
			return (1);
	}
	if (update_var(env_list, "PWD", current))
		return (1);
	return (0);
}

int	ft_cd(char **c_args, t_extra x)
{
	char	old_dir[PATH_MAX];

	if (!c_args[1])
	{
		ft_putendl_fd("cd: missing argument", 2);
		return (1);
	}
	if (!getcwd(old_dir, PATH_MAX))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (chdir(c_args[1]) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		if (errno == EACCES)
			ft_putstr_fd("permission denied: ", 2);
		else
			ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(c_args[1], 2);
		return (1);
	}
	return (update_pwd(x.env_list, old_dir));
}
