/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:11:52 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/31 20:22:58 by anktiri          ###   ########.fr       */
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

static void	handle_child_process(t_token *current, t_extra *x)
{
	int	ret;

	ret = 0;
	if (has_redirections_in_token(current))
		ret = handle_redirections_child(current, x);
	if (ret == 0 && x->pipe_count > 0)
		ret = handle_pipes_child(x, x->cmd_index, count_commands_total(x));
	if (ret == 0)
	{
		if (is_builtin_command(current))
			ret = exec_builtin_child(current, x);
		else
			ret = exec_external_child(current, x);
	}
	if (ret != 0)
		x->exit_status = ret;
	cleanup_child_process(x);
	exit(x->exit_status);
}

static int	cleanup_and_free(t_extra *x, pid_t *pids)
{
	cleanup_pipes(x);
	free(pids);
	return (cleanup_execution_vars(x));
}

static void	restore_std_fds(t_extra *x)
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

static int	exec_loop(t_token *current, pid_t *pids, int cmd_count, 
			t_extra *x, int *i)
{
	while (current && *i < cmd_count)
	{
		if (is_command_token(current))
		{
			pids[*i] = fork();
			if (pids[*i] == 0)
				handle_child_process(current, x);
			else if (pids[*i] < 0)
			{
				handle_fork_error(x);
				return (1);
			}
			else
			{
				if (handle_parent_process(x, *i) != 0)
					return (1);
			}
			x->cmd_index++;
			(*i)++;
		}
		current = current->next;
	}
	return (0);
}

static int	exec_single_builtin(t_token *data, t_extra *x)
{
	t_token	*cmd_token;
	int		ret;

	cmd_token = find_command_token(data);
	if (!cmd_token)
		return (1);
	ret = 0;
	if (has_redirections_in_token(cmd_token))
	{
		x->stdin_backup = dup(STDIN_FILENO);
		x->stdout_backup = dup(STDOUT_FILENO);
		if (x->stdin_backup == -1 || x->stdout_backup == -1)
			return (1);
		if (handle_redirections_child(cmd_token, x) != 0)
			ret = 1;
		if (ret == 0)
			ret = exec_builtin_child(cmd_token, x);
		restore_std_fds(x);
	}
	else
		ret = exec_builtin_child(cmd_token, x);
	cleanup_execution_vars(x);
	return (ret);
}

int	exec_cmd(t_token *data, t_extra *x)
{
	t_token	*current;
	pid_t	*pids;
	int		cmd_count;
	int		i;

	if (!data)
		return (1);
	if (init_execution_vars(x) != 0)
		return (1);
	cmd_count = count_commands(data);
	if (cmd_count == 0)
		return (cleanup_execution_vars(x));
	x->pipe_count = count_pipes(data);
	if (cmd_count == 1 && x->pipe_count == 0 && is_single_builtin(data))
		return (exec_single_builtin(data, x));
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (cleanup_execution_vars(x));
	if (x->pipe_count > 0 && setup_pipes(x) != 0)
		return (cleanup_and_free(x, pids));
	current = data;
	i = 0;
	if (exec_loop(current, pids, cmd_count, x, &i) != 0)
		return (cleanup_and_free(x, pids));
	wait_for_all_children(pids, cmd_count, x);
	cleanup_pipes(x);
	free(pids);
	return (cleanup_execution_vars(x));
}
