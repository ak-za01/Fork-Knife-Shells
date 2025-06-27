/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:53:14 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/26 21:19:49 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

int	handle_ambiguous(int a, int red_s)
{
	if (a < red_s)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int	file_errors(char *file, int output)
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			print_error(file, "Is a directory");
			return (ERROR);
		}
		if (output && access(file, W_OK) != 0)
		{
			print_error(file, "Permission denied");
			return (ERROR);
		}
		if (!output && access(file, R_OK))
		{
			print_error(file, "Permission denied");
			return (ERROR);
		}
	}
	else if (!output)
		return ((print_error(file, "No such file or directory")), ERROR);
	return (SUCCESS);
}

int	handle_hd(t_token *data)
{
	if (ft_dup2(data->pi_doc[0], STDIN_FILENO) != 0)
		return (ERROR);
	return (SUCCESS);
}

int	restore_std_fds(t_extra *x)
{
	if (x->stdin_backup != -1)
	{
		if (ft_dup2(x->stdin_backup, STDIN_FILENO) != 0)
		{
			x->exit_status = ERROR;
			return (ERROR);
		}
		close(x->stdin_backup);
		x->stdin_backup = -1;
	}
	if (x->stdout_backup != -1)
	{
		if (ft_dup2(x->stdout_backup, STDOUT_FILENO) != 0)
		{
			x->exit_status = ERROR;
			return (ERROR);
		}
		close(x->stdout_backup);
		x->stdout_backup = -1;
	}
	return (SUCCESS);
}
