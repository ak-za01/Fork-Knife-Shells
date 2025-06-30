/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:56:18 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/30 16:45:37 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

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
		if (x->pipefd[i])
		{
			free(x->pipefd[i]);
			x->pipefd[i] = NULL;
		}
		i++;
	}
	free(x->pipefd);
	x->pipefd = NULL;
	x->pipe_count = 0;
}

int	free_pipes(t_extra *x, int i)
{
	int	a;

	a = 0;
	while (a < i)
	{
		if (x->pipefd[a])
		{
			free(x->pipefd[a]);
			x->pipefd[a] = NULL;
		}
		a++;
	}
	free(x->pipefd);
	x->pipefd = NULL;
	return (SUCCESS);
}
