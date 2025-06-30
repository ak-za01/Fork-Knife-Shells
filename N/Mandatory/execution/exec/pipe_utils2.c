/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:46:34 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/30 16:46:45 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	close_pipe_in_parent(t_extra *x)
{
	if (x->cmd_index > 0 && x->pipefd[x->cmd_index - 1][0] != -1)
	{
		close(x->pipefd[x->cmd_index - 1][0]);
		x->pipefd[x->cmd_index - 1][0] = -1;
	}
	if (x->cmd_index < x->cmd_count - 1 && x->pipefd[x->cmd_index][1] != -1)
	{
		close(x->pipefd[x->cmd_index][1]);
		x->pipefd[x->cmd_index][1] = -1;
	}
	x->cmd_index++;
	close(x->stdin_backup);
	x->stdin_backup = -1;
	close(x->stdout_backup);
	x->stdout_backup = -1;
}
