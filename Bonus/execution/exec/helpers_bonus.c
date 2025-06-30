/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:18:51 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/30 17:56:38 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*t;

	int (s), (i), (j), (k);
	if (!s1 || !s2 || !s3)
		return (NULL);
	s = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	t = malloc(s + 1);
	if (!t)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		t[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		t[i++] = s2[j++];
	k = 0;
	while (s3[k] != '\0')
		t[i++] = s3[k++];
	t[i] = '\0';
	return (t);
}

int	ft_dup2(int f1, int f2)
{
	if (dup2(f1, f2) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	cleanup_execution_vars(t_token *data, t_extra *x)
{
	t_token	*current;

	current = data;
	if (x->stdin_backup != -1)
	{
		close(x->stdin_backup);
		x->stdin_backup = -1;
	}
	if (x->stdout_backup != -1)
	{
		close(x->stdout_backup);
		x->stdout_backup = -1;
	}
	if (x->pipe_count > 0)
		free_pipe(x);
	while (current)
	{
		if (has_heredoc(current->c_red) && current->pi_doc[0] != -1)
		{
			close(current->pi_doc[0]);
			current->pi_doc[0] = -1;
		}
		current = current->next;
	}
	return (x->exit_status);
}

void	print_error(char *file, char *error_msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	ft_check33(char *t, char *ar)
{
	if ((ft_strnstr(t, ar, ft_strlen(ar)) != NULL) && (ft_strlen(t)
			- 1 == ft_strlen(ar)))
		return (1);
	return (0);
}
