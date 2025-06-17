/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:49:37 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/17 21:47:21 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

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
			if (current->type == pipe_t)
				count++;
		}
		current = current->next;
	}
	return (count);
}

void	free_pipe(t_extra *x)
{
	int	i;

	i = 0;
	while (i < x->pipe_count)
	{
        free(x->pipefd[i]);
		i++;
	}
    free(x->pipefd);
}

void	close_all_pipes(t_extra *x)
{
	int	i;

	i = 0;
	while (i < x->pipe_count)
	{
		close(x->pipefd[i][0]);
		close(x->pipefd[i][1]);
		i++;
	}
}

void close_pipe_in_parent(t_extra *x)
{
    if (x->cmd_index > 0)
        close(x->pipefd[x->cmd_index - 1][0]);
    if (x->cmd_index < x->cmd_count - 1)
        close(x->pipefd[x->cmd_index][1]);
    x->cmd_index++;
}

int	free_pipes(t_extra *x, int i)
{
	int	a;

	a = 0;
	while (a < i)
	{
		if (x->pipefd[a])
			free(x->pipefd[a]);
		a++;
	}
	free(x->pipefd);
	return (SUCCESS);
}

int	create_pipe(t_extra *x)
{
	int	a;

	a = 0;
	if (!x->pipe_count)
		return (ERROR);
	x->pipefd = malloc(x->pipe_count * sizeof(int *));
	if (!x->pipefd)
		return (ERROR);
	while (a < x->pipe_count)
	{
		x->pipefd[a] = malloc(2 * sizeof(int));
		if (!x->pipefd[a])
		{
			ft_putstr_fd("pipe", STDERR_FILENO);
			return ((free_pipes(x, a)), ERROR);
		}
		if (pipe(x->pipefd[a]) == -1)
		{
			ft_putstr_fd("malloc", STDERR_FILENO);
			return ((free_pipes(x, a)), ERROR);
		}
		a++;
	}
	return (SUCCESS);
}

int	setup_pipe(int index, int cmd_count, int **pipefd)
{
	int	a;

	a = 0;
	if (index > 0)
	{
		if (ft_dup2(pipefd[index - 1][0], STDIN_FILENO) != 0)
			return (ERROR);
	}
	if (index < cmd_count - 1)
	{
		if (ft_dup2(pipefd[index][1], STDOUT_FILENO) != 0)
			return (ERROR);
	}
	while (a < cmd_count - 1)
	{
		close(pipefd[a][0]);
		close(pipefd[a][1]);
		a++;
	}
	return (SUCCESS);
}
