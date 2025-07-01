/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:22:54 by anktiri           #+#    #+#             */
/*   Updated: 2025/07/01 12:31:09 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

int	handle_heredoc1(char *del, t_token *data, t_extra *x)
{
	char	*line;
	int		f;

	while (1)
	{
		if (check_signal(data, NULL, 0))
			return (1);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (check_signal(data, line, 0))
			return (free(line), 1);
		if (!line)
			break ;
		f = filter_heredoc_line(&line, del, x);
		if (f == -1)
			return (free(line), -1);
		if (f == 1)
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (SUCCESS);
}

int	handle_heredoc2(char *del, t_token *data, t_extra *x)
{
	char	*line;
	int		f;

	while (1)
	{
		if (check_signal(data, NULL, 1))
			return (1);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (check_signal(data, line, 1))
			return (free(line), 1);
		if (!line)
			break ;
		f = filter_heredoc_line(&line, del, x);
		if (f == -1)
			return (free(line), -1);
		if (f == 1)
		{
			free(line);
			break ;
		}
		(ft_putstr_fd(line, data->pi_doc[1]), free(line));
	}
	(close(data->pi_doc[0]), close(data->pi_doc[1]));
	return (SUCCESS);
}

int	process_heredoc(t_token *data, t_extra *x, int a, int c2)
{
	int	count;

	count = count_heredoc(data);
	while (a < data->red_s)
	{
		if (data->c_red[a] && ft_strcmp(data->c_red[a], "<<") == 0)
		{
			if (c2 == (count - 1))
			{
				if (handle_heredoc2(data->c_red[++a], data, x) != 0)
					return (ERROR);
				c2++;
			}
			else
			{
				if (handle_heredoc1(data->c_red[++a], data, x) != 0)
					return (ERROR);
				c2++;
			}
		}
		else
			a++;
	}
	return ((x->exit_status = 0));
}

int	handle_single_heredoc(t_token *current, t_extra *x)
{
	pid_t	pid;
	int		status;

	if (pipe(current->pi_doc) == -1)
		return ((perror("pipe")), ERROR);
	pid = fork();
	if (pid == 0)
	{
		signal_init_heredoc();
		if (current->c_red)
		{
			if (process_heredoc(current, x, 0, 0) != 0)
				exit(ERROR);
		}
		exit(SUCCESS);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			x->exit_status = WEXITSTATUS(status);
		signal_init_interactive();
	}
	return (close(current->pi_doc[1]), x->exit_status);
}

int	setup_heredoc(t_token *data, t_extra *x)
{
	t_token	*current;

	current = data;
	while (current)
	{
		if (has_heredoc(current->c_red))
		{
			if (handle_single_heredoc(current, x) != SUCCESS)
				return (ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}
