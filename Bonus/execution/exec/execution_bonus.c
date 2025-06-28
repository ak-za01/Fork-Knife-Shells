/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:11:52 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/28 20:18:00 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

int	init_execution_vars(t_token *data, t_extra *x)
{
	x->stdin_backup = dup(STDIN_FILENO);
	if (x->stdin_backup == -1)
		return (ERROR);
	x->stdout_backup = dup(STDOUT_FILENO);
	if (x->stdout_backup == -1)
		return (ERROR);
	x->pipe_count = pipes_count(data);
	x->cmd_count = x->pipe_count + 1;
	x->cmd_index = 0;
	return (SUCCESS);
}

int	ft_execution(t_token *data, t_extra *x)
{
	int	a;

	a = 0;
	if (init_execution_vars(data, x) != 0)
		return (ERROR);
	if (setup_heredoc(data, x) != 0)
	{
		close(data->pi_doc[0]);
		close (x->stdin_backup);
		close (x->stdout_backup);
		return (ERROR);
	}
	if (x->cmd_count == 1 && data->type == b_cmd_t)
		return (exec_single(data, x));
	signal_init_exec();
	exec_external(data, x);
	signal_init_interactive();
	return (cleanup_execution_vars(data, x));
}
