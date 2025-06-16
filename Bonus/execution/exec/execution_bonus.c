/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:11:52 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/16 21:30:17 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

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
	x->cmd_index = 0;
	return (SUCCESS);
}

void	external_helper(t_token *current, t_extra *x)
{
	pid_t pid;
	while (current)
	{
		if (current->type == b_cmd_t || current->type == cmd_t)
		{
			pid = fork();
			if (pid == 0)
			{
				if (x->pipe_count > 0)
					setup_pipe(x->cmd_index, x->cmd_count, x->pipefd);
				exec_child(current, x);
			}
			else if (pid == -1)
			{
				x->exit_status = (perror("fork"), 1);
				break;
			}
			close_pipe_in_parent(x);
		}
		current = current->next;
	}
}

int exec_external(t_token *data, t_extra *x)
{
	t_token *current;

	current = data;
	if (x->pipe_count > 0)
	{
		if (create_pipe(x) != SUCCESS)
			return (perror("pipe creation failed"), 1);
	}
	external_helper(current, x);
	close_all_pipes(x);
	return (x->exit_status);
}

int	exec_cmd(t_token *data, t_extra *x)
{
	int		a;
	int		status;

	a = 0;
	if (init_execution_vars(data, x) != 0)
		return (ERROR);
	// if (setup_heredoc(data, x) != 0)
	// 	return (x->exit_status);
	if (x->cmd_count == 1 && data->type == b_cmd_t)
		return (exec_single(data, x));
	if (exec_external(data, x) != 0)
		return (ERROR);
	while (a < x->cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status))
			waitpid(-1, &x->exit_status, 0);
		a++;
	}
	return (cleanup_execution_vars(x));
}
