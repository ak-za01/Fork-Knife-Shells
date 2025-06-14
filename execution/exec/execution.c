/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:11:52 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/14 12:42:51 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	init_execution_vars(t_token *data, t_extra *x)
{
	x->stdin_backup = dup(STDIN_FILENO);
	if (x->stdin_backup == -1)
		return (ERROR);
	x->stdout_backup = dup(STDOUT_FILENO);
	if (x->stdout_backup == -1)
		return (ERROR);
	x->pipe_count = pipes_count(data);
	x->cmd_count = x->pipe_count + 1;
	x->pipefd = create_pipe(data, x);
	if (x->pipe_count > 0 && !x->pipefd)
		return (ERROR);
	x->cmd_index = 0;
	return (SUCCESS);
}

int	exec_cmd(t_token *data, t_extra *x)
{
	int		a;
	int		status;

	a = 0;
	if (init_execution_vars(data, x) != 0)
		return (ERROR);
	if (setup_heredoc(data, x) != 0)
		return (x->exit_status);
	if (x->cmd_count == 1 && data->type == b_cmd_t)
		return (exec_single(data, x));
	if (exec_external(data, x) != 0)
		return (ERROR);
	while (a < x->cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status))
			x->exit_status = WEXITSTATUS(status);
		a++;
	}
	return (cleanup_execution_vars(x));
}
