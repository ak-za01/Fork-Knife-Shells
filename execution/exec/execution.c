/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:11:52 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/26 19:47:11 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	exec_cmd(t_token *data, t_extra x)
{
	if (data->type == b_cmd_t)
		x.exit_status = exec_builtin(data, x);
	else if (data->type == cmd_t)
		x.exit_status = exec_single(data, x);
	return (x.exit_status);
	
}
