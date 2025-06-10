/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:33:17 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/01 20:57:07 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	file_errors(char *file, int output, t_extra *x)
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			print_error(file, "Is a directory");
			return (-1);
		}
		if (output && access(file, W_OK) != 0)
		{
			print_error(file, "Permission denied");
			return (-1);
		}
		if (!output && access(file, R_OK))
		{
			print_error(file, "Permission denied");
			return (-1);
		}
	}
	else if (!output)
		return ((print_error(file, "No Such file or directory")), -1);
	return (0);
}

int	handle_output(char *file, int append, t_extra *x)
{
	int	fd;

	if (file_errors(file, 1, x) == -1)
		return (-1);
	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(file, "Permission denied");
		x->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_input(char *file, t_extra *x)
{
	int	fd;

	if (file_errors(file, 0, x) == -1)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error(file, "No such file or directory");
		x->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	process_redirection(char **c_red, t_extra *x)
{
	int	a;

	a = 0;
	while (c_red[a])
	{
		if (ft_strcmp(c_red[a], ">") == 0)
		{
			if (handle_output(c_red[++a], 0, x) == -1)
				return (-1);
		}
		else if (ft_strcmp(c_red[a], ">>") == 0)
		{
			if (handle_output(c_red[++a], 1, x) == -1)
				return (-1);
		}
		if (ft_strcmp(c_red[a], "<") == 0)
		{
			if (handle_input(c_red[++a], x) == -1)
				return (-1);
		}
		else
			a++;
	}
	return (0);
}

int	setup_redirections(t_token *data, t_extra *x)
{
	t_token	*current;

	current = data;
	while (current)
	{
		if (current->c_red)
		{
			if (process_redirection(current->c_red, x) != 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
