/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:49:37 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/27 16:14:47 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	failled_pipes(t_extra *x)
{
	int	i;

	i = 0;
	while (i < x->cmd_index - 1)
	{
		if (x->pipefd[i][0] != -1)
		{
			close(x->pipefd[i][0]);
			x->pipefd[i][0] = -1;
		}
		if (x->pipefd[i][1] != -1)
		{
			close(x->pipefd[i][1]);
			x->pipefd[i][1] = -1;
		}
		i++;
	}
}

void	close_all_pipes(t_extra *x)
{
	int	i;

	i = 0;
	while (i < x->pipe_count)
	{
		if (x->pipefd[i][0] != -1)
		{
			close(x->pipefd[i][0]);
			x->pipefd[i][0] = -1;
		}
		if (x->pipefd[i][1] != -1)
		{
			close(x->pipefd[i][1]);
			x->pipefd[i][1] = -1;
		}
		i++;
	}
}

void	close_pipe_in_parent(t_extra *x)
{
	if (x->cmd_index > 0)
		close(x->pipefd[x->cmd_index - 1][0]);
	if (x->cmd_index < x->cmd_count - 1)
		close(x->pipefd[x->cmd_index][1]);
	x->cmd_index++;
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
