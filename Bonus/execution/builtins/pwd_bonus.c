/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:01:40 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/26 21:14:49 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (SUCCESS);
	}
	else
	{
		perror("getcwd() error");
		return (ERROR);
	}
}
