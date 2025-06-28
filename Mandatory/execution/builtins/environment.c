/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:53:28 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/28 18:54:31 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	add(t_env *env_list, char *name, char *value)
{
	if (add_var(env_list, name, value))
	{
		free(env_list->name);
		free(env_list->value);
		free(env_list);
		return (1);
	}
	return (0);
}

t_env	*create_env(void)
{
	t_env	*env_list;
	char	cwd[1024];

	env_list = malloc(sizeof(t_env));
	if (!env_list)
		return (NULL);
	env_list->name = ft_strdup("OLDPWD");
	env_list->value = NULL;
	env_list->next = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		free(env_list->name);
		free(env_list->value);
		free(env_list);
		return (NULL);
	}
	if (add(env_list, "PWD", cwd))
		return (NULL);
	if (add(env_list, "SHLVL", "0"))
		return (NULL);
	return (env_list);
}

int	ft_env(t_token *data, t_extra *x)
{
	t_env	*current;

	(void)data;
	if (!x->env_list)
		return (ERROR);
	current = x->env_list;
	while (current)
	{
		if (current->value && current->name)
		{
			ft_putstr_fd(current->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\n", 1);
		}
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
			if (new_value < 0)
				new_value = 0;
			else
				new_value++;
			if (new_value >= 1000)
				new_value = ((shellvl_error(new_value)), 1);
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
	if (env && *env)
		x->env_list = create_env_list(env);
	else
		x->env_list = create_env();
	if (!var_exist(x->env_list, "OLDPWD"))
	{
		if (add_var(x->env_list, "OLDPWD", NULL))
			return ;
	}
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
	x->exit_status = 0;
}
