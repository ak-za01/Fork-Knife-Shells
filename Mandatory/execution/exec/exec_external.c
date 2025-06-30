/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:48:57 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/30 16:58:09 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

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

static void	set_exit_status(t_extra *x, int status, int is_last)
{
	if (!is_last)
		return ;
	if (WIFEXITED(status))
		x->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			x->exit_status = 130;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			x->exit_status = 131;
		}
	}
}

static void	wait_all_children(t_extra *x)
{
	int	i;
	int	status;

	i = 0;
	while (i < x->cmd_count)
	{
		if (x->child_pids[i] != -1)
		{
			if (waitpid(x->child_pids[i], &status, 0) == -1)
				perror("waitpid");
			else
				set_exit_status(x, status, (i == x->cmd_count - 1));
		}
		i++;
	}
}

int	exec_external(t_token *data, t_extra *x)
{
	if (x->pipe_count > 0)
	{
		if (create_pipe(x) != SUCCESS)
			return (perror("pipe creation failed"), ERROR);
	}
	if (external_helper(data, x) != SUCCESS)
		return (x->exit_status);
	wait_all_children(x);
	close_all_pipes(x);
	return (x->exit_status);
}
