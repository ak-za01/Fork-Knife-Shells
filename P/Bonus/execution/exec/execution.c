/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:11:52 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/01 20:59:28 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// int	exec_cmd(t_token *data, t_extra x)
// {
// 	if (data->type == b_cmd_t)
// 		x.exit_status = exec_builtin(data, x);
// 	else if (data->type == cmd_t)
// 		x.exit_status = exec_single(data, x);
// 	return (x.exit_status);
// }

static int	init_execution_vars(t_extra *x)
{
	x->stdin_backup = dup(STDIN_FILENO);
	x->stdout_backup = dup(STDOUT_FILENO);
	x->pipe_count = 0;
	x->cmd_index = 0;
	x->pipefd = NULL;
	x->prev_pipe_read = -1;
	return 0;
}

static int	cleanup_execution_vars(t_extra *x)
{
	if (x->stdin_backup != -1)
	{
		dup2(x->stdin_backup, STDIN_FILENO);
		close(x->stdin_backup);
	}
	if (x->stdout_backup != -1)
	{
		dup2(x->stdout_backup, STDOUT_FILENO);
		close(x->stdout_backup);
	}
	if (x->pipefd)
	{
		free(x->pipefd);
		x->pipefd = NULL;
	}
	if (x->prev_pipe_read != -1)
	{
		close(x->prev_pipe_read);
		x->prev_pipe_read = -1;
	}
	return (x->exit_status);
}

// static int	cleanup_and_free(t_extra *x, pid_t *pids)
// {
// 	cleanup_pipes(x);
// 	free(pids);
// 	return (cleanup_execution_vars(x));
// }

void	restore_std_fds(t_extra *x)
{
	if (x->stdin_backup != -1)
	{
		dup2(x->stdin_backup, STDIN_FILENO);
		close(x->stdin_backup);
		x->stdin_backup = -1;
	}
	if (x->stdout_backup != -1)
	{
		dup2(x->stdout_backup, STDOUT_FILENO);
		close(x->stdout_backup);
		x->stdout_backup = -1;
	}
}

int	commands_count(t_token *data)
{
	t_token	*current;
	int		count;

	count = 0;
	current = data;
	while (current)
	{
		if (current->type == cmd_t || current->type == b_cmd_t)
			count++;
		current = current->next;
	}
	return (count);
}

int	pipes_count(t_token *data)
{
	t_token	*current;
	int		count;

	count = 0;
	current = data;
	while (current)
	{
		if (current->value)
		{
			if (ft_strcmp(current->value, "|") == 0)
				count++;
		}
		current = current->next;
	}
	return (count);
}

int	exec_cmd(t_token *data, t_extra *x)
{
	t_token	*current;
	// pid_t	*pids;
	int		cmd_count;
	int		a;

	a = 0;
	current = data;
	if (init_execution_vars(x) != 0)
		return (1);
	if (setup_heredoc(data, x) != 0)
		return (x->exit_status);
	cmd_count = commands_count(data);
	if (cmd_count == 0)
		return (cleanup_execution_vars(x));
	x->pipe_count = pipes_count(data);
	if (cmd_count == 1 && x->pipe_count == 0)
		return (exec_single(data, x));
	// pids = malloc(sizeof(pid_t) * cmd_count);
	// if (!pids)
	// 	return (cleanup_execution_vars(x));
	// if (x->pipe_count > 0 && setup_pipes(x) != 0)
	// 	return (cleanup_and_free(x, pids));
	// if (exec_loop(current, pids, cmd_count, x) != 0)
	// 	return (cleanup_and_free(x, pids));
	// wait_for_all_children(pids, cmd_count, x);
	// cleanup_pipes(x);
	// free(pids);
	return (cleanup_execution_vars(x));
}
