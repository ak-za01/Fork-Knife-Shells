/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:13:15 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/16 21:30:14 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

char	*find_path(char	*cmd, t_env *env_list)
{
	char	**paths;
	char	*cmd_path;
	int		i;
	
	i = 0;
	// cmd = ft_split2(t, ' ');
	// if (!cmd || !*cmd || cmd[0][0] == '.')
	// 	(ft_free2(data->pi, data->c - 1), ft_free(cmd),
	// 		perror("execve Error: line 23"), exit(1));	
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

void	exec_child(t_token *data, t_extra *x)
{
	signal_init_child();
	if (data->c_red)
	{
		if (setup_redirections(data, x) != 0)
			exit(1);
	}
	if (data->type == b_cmd_t)
		exit(x->exit_status = exec_builtin(data, *x));
	if (!data->value)
		exit (0);
	x->cmd_path = find_path(data->value, x->env_list);
	if (!x->cmd_path)
		exit(cmd_error(data->value, 127));
	x->env = env_to_arr(x->env_list);
	if (!x->env)
	{
		free(x->cmd_path);
		exit(1);
	}
	execve(x->cmd_path, data->c_arg, x->env);
	perror("execve");
	free_external(x->cmd_path, x->env);
	exit(127);
}

int	exec_single(t_token *data, t_extra *x)
{
	if (setup_redirections(data, x) != 0)
	{
		restore_std_fds(x);
		return ((x->exit_status = 1));
	}
	x->exit_status = exec_builtin(data, *x);
	if (restore_std_fds(x) != 0)
		return ((x->exit_status = ERROR));
	return (x->exit_status);
}
