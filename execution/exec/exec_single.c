/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:13:15 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/01 17:47:07 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

char	*find_path(char	*cmd, t_env *env_list)
{
	char	**paths;
	char	*cmd_path;
	int		i;
	
	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = ft_split(get_env_value(env_list, "PATH"), ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		cmd_path = ft_strjoin3(paths[i], "/", cmd);
		if (cmd_path && access(cmd_path, F_OK | X_OK) == 0)
			return((ft_free(paths)), cmd_path);
		free(cmd_path);
		i++;
	}
	ft_free(paths);
	return (NULL);
}

char	**env_to_arr(t_env *env_list)
{
	t_env	*current;
	char	**env;
	int		count;
	int		i;

	i = 0;
	count = 0;
	current = env_list;
	while (current)
	{
		if (current->original)
			count++;
		current = current->next;
	}
	env = ft_calloc((count + 1), sizeof (char *));
	if (!env)
		return (NULL);
	current = env_list;
	while (current)
	{
		if (current->original)
			env[i++] = ft_strjoin3(current->name, "=", current->value);
		current = current->next;
	}
	return (env);
}

void	free_external(char *cmd_path, char **env)
{
	if (cmd_path)
		free(cmd_path);
	if (env)
		ft_free(env);
}

void	free_exit(char *command_path, char **env_array, int exit_code)
{
	free_external(command_path, env_array);
	exit(exit_code);
}

static void	exec_child(char *cmd_path, char **args, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(cmd_path, args, env) == -1)
	{
		perror("execve");
		free_external(cmd_path, env);
		exit(127);
	}
}

static int	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	cmd_error(char *cmd, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (status);
}

int	exec_external(t_token *data, t_extra x)
{
	char	**env;
	char	*cmd_path;
	pid_t	pid;

	if (!data->value)
		return (1);
	cmd_path = find_path(data->value, x.env_list);
	if (!cmd_path)
		return (cmd_error(data->value, (x.exit_status = 127)));
	env = env_to_arr(x.env_list);
	if (!env)
		return (free(cmd_path), 1);
	pid = fork();
	if (pid == 0)
		exec_child(cmd_path, data->c_arg, env);
	else if (pid > 0)
		x.exit_status = wait_child(pid);
	else
		x.exit_status = (perror("fork"), 1);
	return (free_external(cmd_path, env), x.exit_status);
}

int	exec_single(t_token *data, t_extra *x)
{
	if (setup_redirections(data, x) != 0)
	{
		restore_std_fds(x);
		return ((x->exit_status = 1));
	}
	if (data->type == b_cmd_t)
		x->exit_status = exec_builtin(data, *x);
	else if (data->type == cmd_t)
		x->exit_status = exec_external(data, *x);
	restore_std_fds(x);
	return (x->exit_status);
}
