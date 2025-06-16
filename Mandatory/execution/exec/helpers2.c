/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:17:36 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/16 18:29:04 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	cmd_error(char *cmd, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (status);
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

int	handle_ambiguous(int a, int red_s)
{
	if(a < red_s)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}
