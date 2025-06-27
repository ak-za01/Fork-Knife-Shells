/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:48:57 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/26 21:19:30 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

char	*find_path(char *cmd, t_env *env_list, int i)
{
	char	**paths;
	char	*cmd_path;

	if (!cmd || !*cmd || (ft_strlen(cmd) == 1 && cmd[0] == '.'))
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		return (ft_strdup(cmd));
	}
	else if (!var_exist(env_list, "PATH"))
		return (cmd);
	paths = ft_split(get_env_value(env_list, "PATH"), ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		cmd_path = ft_strjoin3(paths[i], "/", cmd);
		if (cmd_path && access(cmd_path, F_OK | X_OK) == 0)
			return ((ft_free(paths)), cmd_path);
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
		if (current->value)
			count++;
		current = current->next;
	}
	env = ft_calloc((count + 1), sizeof(char *));
	if (!env)
		return (NULL);
	current = env_list;
	while (current)
	{
		if (current->value)
			env[i++] = ft_strjoin3(current->name, "=", current->value);
		current = current->next;
	}
	return (env);
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

void	external_helper(t_token *current, t_extra *x)
{
	pid_t	pid;

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
				failled_pipes(x);
				x->exit_status = (perror("fork"), 1);
				break ;
			}
			close_pipe_in_parent(x);
		}
		else if (current->type == skip_t)
			close_pipe_in_parent(x);
		current = current->next;
	}
}

int	exec_external(t_token *data, t_extra *x)
{
	t_token	*current;

	int (status), a = 0;
	current = data;
	if (x->pipe_count > 0)
	{
		if (create_pipe(x) != SUCCESS)
			return (perror("pipe creation failed"), 1);
	}
	external_helper(current, x);
	while (a < x->cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status))
			x->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				x->exit_status = 130;
			else if (WTERMSIG(status) == SIGQUIT)
				(ft_putstr_fd("Quit: 3\n", 2), x->exit_status = 131);
		}
		a++;
	}
	return (close_all_pipes(x), x->exit_status);
}
