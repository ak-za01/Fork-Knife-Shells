/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:49:37 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/14 08:46:40 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	*free_pipes(t_extra *x, int i)
{
	int	a;

	a = 0;
	if (i)
	{
		while (a < i)
		{
			if (x->pipefd[a])
				free(x->pipefd[a]);
			a++;
		}
	}
	else
	{
		while (a < x->pipe_count)
		{
			if (x->pipefd[a])
				free(x->pipefd[a]);
			a++;
		}
	}
	free(x->pipefd);
	x->pipefd = NULL;
	return (NULL);
}

int	**create_pipe(t_token *data, t_extra *x)
{
	int	a;
	int	**pipefd;

	a = 0;
	if (!x->pipe_count)
		return (NULL);
	if (x->pipe_count > 0)
	{
		pipefd = malloc(x->pipe_count * sizeof(int *));
		if (!pipefd)
			return (NULL);
		while (a < x->pipe_count)
		{
			pipefd[a] = malloc (2 * sizeof(int));
			if (!pipefd[a] || pipe(pipefd[a]))
			{
				perror("pipe");
				return (free_pipes(x, a));
			}
			a++;
		}
		return (pipefd);
	}
	return (NULL);
}

int	setup_pipe(t_extra *x)
{
	int	a;

	a = 0;
	if (x->cmd_index > 0)
	{
		if (ft_dup2(x->pipefd[x->cmd_index - 1][0], STDIN_FILENO) != 0)
			return (ERROR);
	}
	if (x->cmd_index < x->pipe_count)
	{
		if (ft_dup2(x->pipefd[x->cmd_index][1], STDOUT_FILENO) != 0)
			return (ERROR);
	}
	while (a < x->pipe_count)
	{
		close(x->pipefd[a][0]);
		close(x->pipefd[a][1]);
		a++;
	}
	return (SUCCESS);
}
