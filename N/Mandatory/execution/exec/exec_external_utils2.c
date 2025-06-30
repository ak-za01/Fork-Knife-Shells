/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:49:04 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/30 16:58:05 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	init_child_pids(t_extra *x)
{
	int	i;

	x->child_pids = malloc(x->cmd_count * sizeof(pid_t));
	if (!x->child_pids)
		return (perror("malloc failed for child_pids"), ERROR);
	i = 0;
	while (i < x->cmd_count)
	{
		x->child_pids[i] = -1;
		i++;
	}
	return (SUCCESS);
}

static int	handle_fork_failure(t_extra *x, int cmd_idx)
{
	int	i;
	int	status;

	perror("fork");
	x->exit_status = 1;
	close_all_pipes(x);
	i = 0;
	while (i < cmd_idx)
	{
		if (x->child_pids[i] != -1)
			waitpid(x->child_pids[i], &status, 0);
		i++;
	}
	return (x->exit_status);
}

void	exec_child(t_token *data, t_extra *x)
{
	int	f;

	signal_init_child();
	if (data->c_red)
	{
		if (setup_redirections(data, x) != 0)
			exit(1);
	}
	if (data->type == b_cmd_t)
		exit(exec_builtin(data, x));
	if (!data->value)
		exit(0);
	x->cmd_path = find_path(data->value, x->env_list, 0);
	if (!x->cmd_path)
		exit(cmd_error1(data->value));
	f = file_errors2(x->cmd_path);
	if (f != 0)
		exit(cmd_error(data->value, f));
	x->env = env_to_arr(x->env_list);
	if (!x->env)
		(free(x->cmd_path), exit(1));
	execve(x->cmd_path, data->c_arg, x->env);
	perror("execve");
	free_external(x->cmd_path, x->env);
	exit(126);
}

static int	process_command(t_token *current, t_extra *x, int *cmd_idx)
{
	pid_t	pid;

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
			return (handle_fork_failure(x, *cmd_idx));
		else
		{
			x->child_pids[(*cmd_idx)++] = pid;
			close_pipe_in_parent(x);
		}
	}
	else if (current->type == skip_t)
		close_pipe_in_parent(x);
	return (SUCCESS);
}

int	external_helper(t_token *current, t_extra *x)
{
	int	cmd_idx;
	int	result;

	cmd_idx = 0;
	if (init_child_pids(x) != SUCCESS)
		return (ERROR);
	while (current)
	{
		result = process_command(current, x, &cmd_idx);
		if (result != SUCCESS)
			return (result);
		current = current->next;
	}
	return (SUCCESS);
}
