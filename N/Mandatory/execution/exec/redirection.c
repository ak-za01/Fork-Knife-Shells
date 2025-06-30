/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:33:17 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/30 16:58:32 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	handle_output(char *file, int append, t_extra *x)
{
	int	fd;

	if (file_errors(file, 1) != 0)
		return (ERROR);
	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		x->exit_status = 1;
		return (ERROR);
	}
	if (ft_dup2(fd, STDOUT_FILENO) != 0)
		return (ERROR);
	close(fd);
	return (SUCCESS);
}

int	handle_input(char *file, t_extra *x)
{
	int	fd;

	if (file_errors(file, 0) != 0)
		return (ERROR);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		x->exit_status = 1;
		return (ERROR);
	}
	if (ft_dup2(fd, STDIN_FILENO) != 0)
		return (ERROR);
	close(fd);
	return (SUCCESS);
}

int	check_redirection(t_token *data, t_extra *x, int *a)
{
	if (ft_strcmp(data->c_red[*a], ">") == 0)
	{
		if (handle_output(data->c_red[++(*a)], 0, x) != 0)
			return (ERROR);
	}
	else if (ft_strcmp(data->c_red[*a], ">>") == 0)
	{
		if (handle_output(data->c_red[++(*a)], 1, x) != 0)
			return (ERROR);
	}
	else if (ft_strcmp(data->c_red[*a], "<") == 0)
	{
		if (handle_input(data->c_red[++(*a)], x) != 0)
			return (ERROR);
	}
	else if (ft_strcmp(data->c_red[*a], "<<") == 0)
	{
		if (handle_hd(data) != 0)
			return (ERROR);
		(*a)++;
	}
	return (SUCCESS);
}

int	process_redirection(t_token *data, t_extra *x, int a)
{
	while (a < data->red_s && data->c_red[a])
	{
		if (!data->c_red[a + 1])
			break ;
		if (check_redirection(data, x, &a) != 0)
			return (ERROR);
		a++;
	}
	return (handle_ambiguous(a, data->red_s));
}

int	setup_redirections(t_token *data, t_extra *x)
{
	t_token	*current;

	current = data;
	if (current && current->c_red)
	{
		if (process_redirection(current, x, 0) != 0)
			return (ERROR);
	}
	return (SUCCESS);
}
