/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:26:23 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/28 20:17:37 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

void	chdir_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(path, 2);
}

int	expand_tilde(char *home, char *path, char *old_dir, t_extra *x)
{
	char	*expanded_path;
	int		i;
	int		j;

	if (path[1] != '\0' && path[1] != '/')
	{
		if (chdir(path) != 0)
			return (chdir_error(path), 1);
		return (update_pwd(x, old_dir));
	}
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
		chdir_error(expanded_path);
		return (free(expanded_path), 1);
	}
	return (free(expanded_path), update_pwd(x, old_dir));
}
