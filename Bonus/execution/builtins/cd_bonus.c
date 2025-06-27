/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:27:50 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/26 21:14:27 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

char	*get_env_value(t_env *env_list, char *name)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	handle_home(t_extra *x, char *old_dir)
{
	char	*home;

	home = get_env_value(x->env_list, "HOME");
	if (!home || home[0] == '\0')
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return ((x->exit_status = 1));
	}
	if (chdir(home) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(home, 2);
		return ((x->exit_status = 1));
	}
	return (update_pwd(x, old_dir));
}

int	handle_cd_dash(t_extra *x, char *old_dir)
{
	char	*oldpwd;

	oldpwd = get_env_value(x->env_list, "OLDPWD");
	if (!oldpwd || oldpwd[0] == '\0')
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return ((x->exit_status = 1));
	}
	if (chdir(oldpwd) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(oldpwd, 2);
		return ((x->exit_status = 1));
	}
	ft_putendl_fd(oldpwd, 1);
	return (update_pwd(x, old_dir));
}

int	ft_cd(char **c_args, t_extra *x)
{
	char	old_dir[PATH_MAX];

	if (!getcwd(old_dir, PATH_MAX) && !var_exist(x->env_list, "PWD"))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ((x->exit_status = 1));
	}
	if (!c_args[1])
		return (handle_home(x, old_dir));
	else if ((ft_strcmp(c_args[1], "-") == 0) || (ft_strcmp(c_args[1],
				"--") == 0))
		return (handle_cd_dash(x, old_dir));
	if (chdir(c_args[1]) != 0)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		(ft_putstr_fd(c_args[1], 2), ft_putstr_fd(": ", 2));
		if (errno == EACCES)
			ft_putstr_fd("Permission denied: ", 2);
		else
			ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return ((x->exit_status = update_pwd(x, old_dir)));
}
