/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:56:18 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/28 20:18:13 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

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
