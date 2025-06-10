/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:27:50 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/22 11:48:55 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

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

int	expand_tilde(char *home, char *path, char *old_dir, t_extra x)
{
	char	*expanded_path;
	int		i;
	int		j;

	expanded_path = malloc(ft_strlen(home) + ft_strlen(path) + 1);
	if (!expanded_path)
		return (1);
	i = ((j = 1), -1);
	while (home[++i])
		expanded_path[i] = home[i];
	while (path[j])
		expanded_path[i++] = path[j++];
	expanded_path[i] = '\0';
	if (chdir(expanded_path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(expanded_path, 2);
		free(expanded_path);
		return (1);
	}
	free(expanded_path);
	return (update_pwd(x, old_dir));
}

int	handle_cd_tilde(t_extra x, char *old_dir, char *path)
{
	char	*home;

	home = get_env_value(x.env_list, "HOME");
	if (!home || home[0] == '\0')
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return ((x.exit_status = 1));
	}
	if (path)
	{
		if (expand_tilde(home, path, old_dir, x))
			return ((x.exit_status = 1));
		return ((x.exit_status = 0));
	}
	if (chdir(home) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(home, 2);
		return ((x.exit_status = 1));
	}
	return (update_pwd(x, old_dir));
}

int	handle_cd_dash(t_extra x, char *old_dir)
{
	char	*oldpwd;

	oldpwd = get_env_value(x.env_list, "OLDPWD");
	if (!oldpwd || oldpwd[0] == '\0')
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return ((x.exit_status = 1));
	}
	if (chdir(oldpwd) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(oldpwd, 2);
		return ((x.exit_status = 1));
	}
	ft_putendl_fd(oldpwd, 1);
	return (update_pwd(x, old_dir));
}

int	ft_cd(char **c_args, t_extra x)
{
	char	old_dir[PATH_MAX];

	if (!getcwd(old_dir, PATH_MAX))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ((x.exit_status = 1));
	}
	if (!c_args[1] || c_args[1][0] == '~')
		return (handle_cd_tilde(x, old_dir, c_args[1]));
	else if (ft_strcmp(c_args[1], "-") == 0)
		return (handle_cd_dash(x, old_dir));
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
	return ((x.exit_status = update_pwd(x, old_dir)));
}
