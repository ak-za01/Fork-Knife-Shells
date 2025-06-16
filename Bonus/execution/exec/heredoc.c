/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:22:54 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/01 20:59:42 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	print_error(char *file, char *error_msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	has_heredoc(char **c_red)
{
	int	a;

	a = 0;
	while (c_red[a])
	{
		if (ft_strcmp(c_red[a], "<<") == 0)
			return (1);
		a++;
	}
	return (0);
}

int	handle_heredoc(char *del)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return ((perror("pipe")), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipefd[1]);
		ft_putstr_fd("\n", pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	process_heredoc(t_token *data, t_extra *x)
{
	int	fd_heredoc;
	int	a;

	a = 0;
	fd_heredoc = -1;
	while (data->c_red[a])
	{
		if (ft_strcmp(data->c_red[a], "<<") == 0)
		{
			if (fd_heredoc != -1)
				close(fd_heredoc);
			fd_heredoc = handle_heredoc(data->c_red[++a]);
			if (fd_heredoc == -1)
				return (-1);
		}
		else
			a++;
	}
	if (fd_heredoc != -1)
	{
		if (dup2(fd_heredoc, STDIN_FILENO) == -1)
			return ((close(fd_heredoc)), -1);
		close(fd_heredoc);
	}
	return ((x->exit_status = 0));
}

int	setup_heredoc(t_token *data, t_extra *x)
{
	t_token	*current;

	current = data;
	while (current)
	{
		if (current->c_red && has_heredoc(current->c_red))
		{
			if (process_heredoc(current, x) != 0)
				return (-1);
		}
		current = current->next;
	}
	x->exit_status = 0;
	return (0);
}
