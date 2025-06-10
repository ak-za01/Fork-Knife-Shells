#include "../../include/builtins.h"

volatile sig_atomic_t g_signal_received = 0;

/**
 * Create pipes for pipeline execution
 */
int	**create_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	if (pipe_count <= 0)
		return (NULL);
	
	pipes = malloc(sizeof(int *) * pipe_count);
	if (!pipes)
		return (NULL);
	
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			cleanup_partial_pipes(pipes, i);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			free(pipes[i]);
			cleanup_partial_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

/**
 * Handle malloc error for pipeline setup
 */
int	handle_malloc_error(int **pipes, pid_t *pids)
{
	if (pipes)
		free(pipes);
	if (pids)
		free(pids);
	return (1);
}

/**
 * Execute child process in pipeline
 */
void	execute_pipeline_child(t_token *current, int **pipes, int i, int pipe_count)
{
	// Setup pipes for this child
	if (i > 0) // Not first command
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
	}
	if (i < pipe_count) // Not last command
	{
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	
	// Close all pipe file descriptors
	close_all_pipes(pipes, pipe_count);
	
	// Setup child signals
	setup_child_signals();
	
	// Execute the command
	if (current->type == b_cmd_t)
	{
		// For builtins in pipeline, we need to exit with the result
		t_extra x_temp = {0}; // Create temporary extra struct
		int result = exec_builtin(current, x_temp);
		exit(result);
	}
	else
	{
		char *command_path = find_command_path(current->value, NULL);
		char **args = prepare_args_from_token(current);
		char **env_array = env_list_to_array(NULL); // You'll need to pass proper env
		
		if (command_path && args && execve(command_path, args, env_array) == -1)
		{
			perror("execve");
			exit(126);
		}
		exit(127); // Command not found
	}
}

/**
 * Handle fork error in pipeline
 */
int	handle_fork_error(int **pipes, pid_t *pids, int pipe_count)
{
	perror("fork");
	cleanup_pipeline(pipes, pids, pipe_count);
	return (1);
}

/**
 * Skip to next command in token list (after pipe)
 */
t_token	*skip_to_next_command(t_token *current)
{
	while (current && current->type != pipe_t)
		current = current->next;
	
	if (current && current->type == pipe_t)
		current = current->next;
	
	return (current);
}

/**
 * Close all pipes in parent process
 */
void	close_all_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes)
		return;
	
	i = 0;
	while (i < pipe_count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

/**
 * Wait for all processes in pipeline
 */
int	wait_for_pipeline(pid_t *pids, int process_count)
{
	int	status;
	int	exit_status;
	int	i;

	exit_status = 0;
	i = 0;
	while (i < process_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == process_count - 1) // Last command determines exit status
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (exit_status);
}

/**
 * Cleanup pipeline resources
 */
void	cleanup_pipeline(int **pipes, pid_t *pids, int pipe_count)
{
	int	i;

	if (pipes)
	{
		i = 0;
		while (i < pipe_count)
		{
			if (pipes[i])
				free(pipes[i]);
			i++;
		}
		free(pipes);
	}
	if (pids)
		free(pids);
}

/**
 * Cleanup partially created pipes (helper function)
 */
static void	cleanup_partial_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*t;
	int		s, i, j, k;  // Fixed syntax error

	if (!s1 || !s2 || !s3)
		return (NULL);
	s = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	t = malloc(s + 1);
	if (!t)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		t[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		t[i++] = s2[j++];
	k = 0;
	while (s3[k] != '\0')
		t[i++] = s3[k++];
	t[i] = '\0';
	return (t);
}

/**
 * Execute a pipeline of commands (cmd1 | cmd2 | cmd3...)
 */
int	execute_pipeline(t_token *data, t_extra *x)
{
	t_token	*current;
	int		pipe_count;
	int		**pipes;
	pid_t	*pids;
	int		i;
	int		exit_status;

	pipe_count = count_pipes(data);
	if (pipe_count == 0)
		return (execute_single_command(data, x));

	// Allocate pipes and process IDs
	pipes = create_pipes(pipe_count);
	pids = malloc(sizeof(pid_t) * (pipe_count + 1));
	if (!pipes || !pids)
		return (handle_malloc_error(pipes, pids));

	// Execute each command in the pipeline
	current = data;
	i = 0;
	while (current)
	{
		if (current->type == pipe_t)
		{
			current = current->next;
			continue;
		}
		
		pids[i] = fork();
		if (pids[i] == 0)
			execute_pipeline_child(current, pipes, i, pipe_count);
		else if (pids[i] < 0)
			return (handle_fork_error(pipes, pids, pipe_count));
		
		current = skip_to_next_command(current);
		i++;
	}

	// Close all pipes in parent and wait for children
	close_all_pipes(pipes, pipe_count);
	exit_status = wait_for_pipeline(pids, pipe_count + 1);
	
	cleanup_pipeline(pipes, pids, pipe_count);
	x->exit_status = exit_status;
	return (exit_status);
}

/**
 * Execute a single command with potential redirections
 */
int	execute_with_redirections(t_token *data, t_extra *x)
{
	int		saved_stdin;
	int		saved_stdout;
	int		exit_status;

	// Save original file descriptors
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		perror("dup");
		return (1);
	}

	// Setup redirections directly from token list
	if (!setup_redirections_from_tokens(data))
	{
		restore_fds(saved_stdin, saved_stdout);
		return (1);
	}

	// Execute the command
	if (data->type == b_cmd_t)
		exit_status = exec_builtin(data, *x);
	else
		exit_status = execute_external_command(data, x);

	// Restore original file descriptors
	restore_fds(saved_stdin, saved_stdout);
	
	x->exit_status = exit_status;
	return (exit_status);
}

/**
 * Setup redirections directly from token list
 */
int	setup_redirections_from_tokens(t_token *data)
{
	t_token	*current;
	int		fd;

	current = data;
	while (current)
	{
		if (current->type == outfile_t && current->next)
		{
			// Handle > redirection
			fd = open(current->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(current->next->value);
				return (0);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (0);
			}
			close(fd);
		}
		else if (current->type == append_t && current->next)
		{
			// Handle >> redirection
			fd = open(current->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd == -1)
			{
				perror(current->next->value);
				return (0);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (0);
			}
			close(fd);
		}
		else if (current->type == infile_t && current->next)
		{
			// Handle < redirection
			fd = open(current->next->value, O_RDONLY);
			if (fd == -1)
			{
				perror(current->next->value);
				return (0);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (0);
			}
			close(fd);
		}
		else if (current->type == heredoc_t && current->next)
		{
			// Handle << redirection
			if (!handle_heredoc(current->next->value))
				return (0);
		}
		current = current->next;
	}
	return (1);
}

/**
 * Handle heredoc (<<) redirection
 */
int	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;
	
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipe_fd[0]);
		return (0);
	}
	close(pipe_fd[0]);
	return (1);
}

/**
 * Execute external (non-builtin) command
 */
int	execute_external_command(t_token *data, t_extra *x)
{
	char	*command_path;
	char	**args;
	char	**env_array;
	pid_t	pid;
	int		status;

	// Find command in PATH or use absolute/relative path
	command_path = find_command_path(data->value, x->env_list);
	if (!command_path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(data->value, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		x->exit_status = 127;
		return (127);
	}

	// Prepare arguments and environment
	args = prepare_args_from_token(data);
	env_array = env_list_to_array(x->env_list);
	if (!args || !env_array)
	{
		cleanup_external_prep(command_path, args, env_array);
		x->exit_status = 1;
		return (1);
	}

	// Fork and execute
	pid = fork();
	if (pid == 0)
	{
		// Child process
		setup_child_signals();
		if (execve(command_path, args, env_array) == -1)
		{
			perror("execve");
			cleanup_and_exit(command_path, args, env_array, 126);
		}
	}
	else if (pid > 0)
	{
		// Parent process
		setup_parent_signals();
		waitpid(pid, &status, 0);
		
		if (WIFEXITED(status))
			x->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			x->exit_status = 128 + WTERMSIG(status);
	}
	else
	{
		perror("fork");
		x->exit_status = 1;
	}

	cleanup_external_prep(command_path, args, env_array);
	return (x->exit_status);
}

/**
 * Execute a single command (builtin or external)
 */
int	execute_single_command(t_token *data, t_extra *x)
{
	if (!data)
		return (x->exit_status);

	if (data->type == b_cmd_t)
		return (exec_builtin(data, *x));
	else if (data->type == cmd_t)
		return (execute_external_command(data, x));
	
	x->exit_status = 1;
	return (1);
}

/**
 * Check if the command list contains pipes
 */
int	is_pipeline(t_token *data)
{
	t_token	*current;

	current = data;
	while (current)
	{
		if (current->type == pipe_t)
			return (1);
		current = current->next;
	}
	return (0);
}

/**
 * Check if the command has redirections
 */
int	has_redirections(t_token *data)
{
	t_token	*current;

	current = data;
	while (current)
	{
		if (current->type == infile_t || current->type == outfile_t ||
			current->type == append_t || current->type == heredoc_t)
			return (1);
		current = current->next;
	}
	return (0);
}

/**
 * Find command in PATH or return absolute/relative path
 */
char	*find_command_path(char *command, t_env *env_list)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	// If command contains '/', it's already a path
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}

	// Get PATH from environment
	path_env = get_env_value(env_list, "PATH");
	if (!path_env)
		return (NULL);

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);

	// Check each PATH directory
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin3(paths[i], "/", command);
		if (full_path && access(full_path, F_OK | X_OK) == 0)
		{
			ft_free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}

	ft_free(paths);
	return (NULL);
}

/**
 * Get environment variable value
 */
char	*get_env_value(t_env *env_list, char *name)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/**
 * Prepare arguments array from token
 */
char	**prepare_args_from_token(t_token *data)
{
	if (data->c_arg && data->arg_s > 0)
		return (ft_split_args(data->c_arg, data->arg_s));
	
	// Fallback: create single argument array
	char **args = malloc(sizeof(char *) * 2);
	if (!args)
		return (NULL);
	args[0] = ft_strdup(data->value);
	args[1] = NULL;
	return (args);
}

/**
 * Convert environment list to array
 */
char	**env_list_to_array(t_env *env_list)
{
	t_env	*current;
	char	**env_array;
	char	*temp;
	int		count;
	int		i;

	// Count environment variables
	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}

	// Allocate array
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);

	// Fill array
	current = env_list;
	i = 0;
	while (current)
	{
		temp = ft_strjoin3(current->name, "=", current->value);
		env_array[i] = temp;
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	
	return (env_array);
}

/**
 * Restore file descriptors
 */
void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

/**
 * Setup signals for child processes
 */
void	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * Setup signals for parent process during execution
 */
void	setup_parent_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * Cleanup after external command preparation
 */
void	cleanup_external_prep(char *command_path, char **args, char **env_array)
{
	if (command_path)
		free(command_path);
	if (args)
		ft_free(args);
	if (env_array)
		ft_free(env_array);
}

/**
 * Cleanup and exit child process
 */
void	cleanup_and_exit(char *command_path, char **args, char **env_array, int exit_code)
{
	cleanup_external_prep(command_path, args, env_array);
	exit(exit_code);
}

/**
 * Count pipes in token list
 */
int	count_pipes(t_token *data)
{
	t_token	*current;
	int		count;

	count = 0;
	current = data;
	while (current)
	{
		if (current->type == pipe_t)
			count++;
		current = current->next;
	}
	return (count);
}

int	execute_command_list(t_token *data, t_extra *x)
{
	int	exit_status;

	if (!data)
		return (x->exit_status);
	
	// Handle different command structures
	if (is_pipeline(data))
		exit_status = execute_pipeline(data, x);
	else if (has_redirections(data))
		exit_status = execute_with_redirections(data, x);
	else if (data->type == b_cmd_t)
		exit_status = exec_builtin(data, *x);
	else if (data->type == cmd_t)
		exit_status = execute_external_command(data, x);
	else
		exit_status = 1; // Unknown command type
	
	x->exit_status = exit_status;
	return (exit_status);
}