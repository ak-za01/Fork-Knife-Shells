/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:05:03 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/13 21:25:55 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	init_execution_vars(t_extra *x)
{
	x->stdin_backup = dup(STDIN_FILENO);
	x->stdout_backup = dup(STDOUT_FILENO);
	x->pipe_count = 0;
	x->cmd_index = 0;
	x->pipefd = NULL;
	return 0;
}

static int	cleanup_execution_vars(t_extra *x)
{
	if (x->stdin_backup != -1)
	{
		if (dup2(x->stdin_backup, STDIN_FILENO) == -1)
			return (close(x->stdin_backup), -1);
		close(x->stdin_backup);
	}
	if (x->stdout_backup != -1)
	{
		if (dup2(x->stdout_backup, STDOUT_FILENO) == -1)
			return (close(x->stdout_backup), -1);
		close(x->stdout_backup);
	}
	if (x->pipefd)
	{
		free(x->pipefd);
		x->pipefd = NULL;
	}
	return (x->exit_status);
}

void	restore_std_fds(t_extra *x)
{
	if (x->stdin_backup != -1)
	{
		if (dup2(x->stdin_backup, STDIN_FILENO) == -1)
		{
			close(x->stdin_backup);
			return ;
		}
		close(x->stdin_backup);
		x->stdin_backup = -1;
	}
	if (x->stdout_backup != -1)
	{
		if (dup2(x->stdout_backup, STDOUT_FILENO) == -1)
		{
			close(x->stdout_backup);
			return ;
		}
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

// Setup pipes for current command in the pipeline
static void	setup_command_pipes(int cmd_index, int pipe_count, int **pipes, int prev_read)
{
	// Connect to previous pipe (stdin)
	if (cmd_index > 0 && prev_read != -1)
	{
		dup2(prev_read, STDIN_FILENO);
		close(prev_read);
	}
	
	// Connect to next pipe (stdout)
	if (cmd_index < pipe_count)
	{
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
	
	// Close all pipe file descriptors in child
	int i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

// Execute single command (builtin or external)
static void	exec_command_child(t_token *data, t_extra *x)
{
	// Reset signal handlers for child
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	
	// Handle heredocs for this command
	if (data->c_red && has_heredoc(data->c_red))
	{
		if (process_heredoc(data, x) != 0)
			exit(1);
	}
	
	// Handle other redirections
	if (data->c_red)
	{
		if (process_redirection(data->c_red, x) != 0)
			exit(1);
	}
	
	// Execute command
	if (data->type == b_cmd_t)
	{
		x->exit_status = exec_builtin(data, *x);
		exit(x->exit_status);
	}
	else if (data->type == cmd_t)
	{
		char *cmd_path = find_path(data->value, x->env_list);
		if (!cmd_path)
		{
			cmd_error(data->value, 127);
			exit(127);
		}
		
		char **env = env_to_arr(x->env_list);
		if (!env)
		{
			free(cmd_path);
			exit(1);
		}
		
		if (execve(cmd_path, data->c_arg, env) == -1)
		{
			perror("execve");
			free_external(cmd_path, env);
			exit(127);
		}
	}
	exit(0);
}

// Execute pipeline
static int	exec_pipeline(t_token *data, t_extra *x)
{
	int		cmd_count = commands_count(data);
	int		pipe_count = pipes_count(data);
	int		**pipes = NULL;
	pid_t	*pids = NULL;
	t_token	*current;
	int		cmd_index = 0;
	int		prev_pipe_read = -1;
	
	// Allocate memory for pipes and process IDs
	if (pipe_count > 0)
	{
		pipes = malloc(sizeof(int*) * pipe_count);
		if (!pipes)
			return (1);
		 
		int i = 0;
		while (i < pipe_count)
		{
			pipes[i] = malloc(sizeof(int) * 2);
			if (!pipes[i] || pipe(pipes[i]) == -1)
			{
				perror("pipe");
				// Cleanup allocated pipes
				int j = 0;
				while (j < i)
				{
					free(pipes[j]);
					j++;
				}
				free(pipes);
				return (1);
			}
			i++;
		}
	}

	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
	{
		// Cleanup pipes
		if (pipes)
		{
			int i = 0;
			while (i < pipe_count)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
				i++;
			}
			free(pipes);
		}
		return (1);
	}
	
	// Execute each command
	current = data;
	while (current)
	{
		if (current->type == cmd_t || current->type == b_cmd_t)
		{
			pid_t pid = fork();
			if (pid == 0)
			{
				// Child process
				if (pipe_count > 0)
					setup_command_pipes(cmd_index, pipe_count, pipes, prev_pipe_read);
				exec_command_child(current, x);
			}
			else if (pid > 0)
			{
				pids[cmd_index] = pid;
				
				// Close previous pipe read end in parent
				if (prev_pipe_read != -1)
					close(prev_pipe_read);
				
				// Set up for next iteration
				if (cmd_index < pipe_count)
				{
					prev_pipe_read = pipes[cmd_index][0];
					close(pipes[cmd_index][1]); // Close write end in parent
				}
				cmd_index++;
			}
			else
			{
				perror("fork");
				x->exit_status = 1;
				break;
			}
		}
		current = current->next;
	}
	
	// Close remaining pipe read end
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
	
	// Wait for all children and get exit status of last command
	int i = 0;
	while (i < cmd_index)
	{
		int status;
		waitpid(pids[i], &status, 0);
		if (i == cmd_index - 1) // Last command determines exit status
		{
			if (WIFEXITED(status))
				x->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				x->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	
	// Cleanup
	if (pipes)
	{
		int i = 0;
		while (i < pipe_count)
		{
			free(pipes[i]);
			i++;
		}
		free(pipes);
	}
	free(pids);
	
	return (x->exit_status);
}

int	exec_cmd(t_token *data, t_extra *x)
{
	int		cmd_count;

	if (init_execution_vars(x) != 0)
		return (1);
		
	// Process ALL heredocs first (before any forking)
	if (setup_heredoc(data, x) != 0)
		return (cleanup_execution_vars(x));
		
	cmd_count = commands_count(data);
	if (cmd_count == 0)
		return (cleanup_execution_vars(x));
		
	x->pipe_count = pipes_count(data);
	
	// Single command - use existing exec_single function
	if (cmd_count == 1 && x->pipe_count == 0)
		return (exec_single(data, x));
	
	// Pipeline execution
	exec_pipeline(data, x);
	
	return (cleanup_execution_vars(x));
}