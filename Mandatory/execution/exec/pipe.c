/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:49:37 by anktiri           #+#    #+#             */
/*   Updated: 2025/07/02 00:11:19 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	init_pipe_arrays(t_extra *x)
{
	int	a;

	x->pipefd = malloc(x->pipe_count * sizeof(int *));
	if (!x->pipefd)
		return (ERROR);
	a = 0;
	while (a < x->pipe_count)
	{
		x->pipefd[a] = NULL;
		a++;
	}
	return (SUCCESS);
}

static int	allocate_pipe_memory(t_extra *x)
{
	int	a;

	a = 0;
	while (a < x->pipe_count)
	{
		x->pipefd[a] = malloc(2 * sizeof(int));
		if (!x->pipefd[a])
		{
			ft_putstr_fd("malloc failed\n", STDERR_FILENO);
			free_pipes(x, a);
			return (ERROR);
		}
		x->pipefd[a][0] = -1;
		x->pipefd[a][1] = -1;
		a++;
	}
	return (SUCCESS);
}

static int	create_all_pipes(t_extra *x)
{
	int	a;
	int	i;

	a = 0;
	while (a < x->pipe_count)
	{
		if (pipe(x->pipefd[a]) == -1)
		{
			i = 0;
			while (i < a)
			{
				close(x->pipefd[i][0]);
				close(x->pipefd[i][1]);
				i++;
			}
			free_pipes(x, x->pipe_count);
			return (ERROR);
		}
		a++;
	}
	return (SUCCESS);
}

int	create_pipe(t_extra *x)
{
	if (!x->pipe_count)
		return (ERROR);
	if (init_pipe_arrays(x) != SUCCESS)
		return (ERROR);
	if (allocate_pipe_memory(x) != SUCCESS)
		return (ERROR);
	if (create_all_pipes(x) != SUCCESS)
		return (ERROR);
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
