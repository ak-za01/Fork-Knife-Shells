/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ext_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:09:48 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/26 21:19:25 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

int	file_errors2(char *file)
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
			return (1);
		if (access(file, F_OK) != 0)
			return (3);
		if (access(file, X_OK) != 0)
			return (2);
	}
	else
		return (3);
	return (0);
}

int	cmd_error(char *cmd, int f)
{
	if (f == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		return (126);
	}
	else if (f == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (126);
	}
	else if (f == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	return (127);
}

void	free_external(char *cmd_path, char **env)
{
	if (cmd_path)
		free(cmd_path);
	if (env)
		ft_free(env);
}

int	cmd_error1(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}
