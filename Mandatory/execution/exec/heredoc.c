/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:22:54 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/24 01:03:56 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	print_error(char *file, char *error_msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	has_heredoc(char **c_red)
{
	int	a;

	if(!c_red)
		return (0);
	a = 0;
	while (c_red[a])
	{
		if (ft_strcmp(c_red[a], "<<") == 0)
			return (1);
		a++;
	}
	return (0);
}

int	count_heredoc(t_token *data)
{
	int	i;
	int	count;

	i=0;
	count = 0;
	while (i < data->red_s)
	{
		if (data->c_red[i] && ft_strcmp(data->c_red[i], "<<") == 0)
			count++;
		i++;
	}
	return (count);
}

int	ft_check33(char *t, char *ar)
{
	if ((ft_strnstr(t, ar, ft_strlen(ar)) != NULL) && (ft_strlen(t)
			- 1 == ft_strlen(ar)))
		return (1);
	return (0);
}

int	ft_check_q_status2(char *t)
{
	int		i;
	int		f;
	char	**s1;

	s1 = ft_split4(t);
	if (!s1)
		return (-1);
	i = 0;
	while (s1[i])
	{
		f = ft_check_q_status(s1[i]);
		if (f != 0)
			return (ft_free(s1), f);
		i++;
	}
	return (ft_free(s1), 0);
}

int	filter_heredoc_line(char **line, char *del, t_extra *x)
{
	int		f1;
	int		f2;
	char	*t1;
	char	*t2;

	t1 = ft_strdup(del);
	if (!t1)
		return (-1);
	f1 = ft_check_q_status2(t1);
	t1 = ft_remove_q(t1);
	if (f1 != 0)
	{
		f2 = ft_check33(*line, t1);
		return (free(t1), f2);
	}
	else
	{
		t2 = ft_strdup(*line);
		if (!t2)
			return (-1);
		free(*line);
		*line = ft_swap_value(0, t2, x, 0);
		f2 = ft_check33(t2, t1);
		return (free(t1),free(t2), f2);
	}
}


int	handle_heredoc1(char *del, t_token *data, t_extra *x)
{
	char	*line;
	int		f;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		f = filter_heredoc_line(&line, del, x);
		if (f == -1)
			return (-1);
		if (f == 1)
			break ;
		free(line);
	}
	return (SUCCESS);
}

int	handle_heredoc2(char *del, t_token *data, t_extra *x)
{
	char	*line;
	int		f;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		f = filter_heredoc_line(&line, del, x);
		if (f == -1)
			return (-1);
		if (f == 1)
			break ;
		ft_putstr_fd(line, data->pi_doc[1]);
		free(line);
	}
	close(data->pi_doc[0]);
	close(data->pi_doc[1]);
	return (SUCCESS);
}

int	process_heredoc(t_token *data, t_extra *x, int a, int c2)
{
	int count;

	count = count_heredoc(data);
	while (a < data->red_s)
	{	
		if (data->c_red[a] && ft_strcmp(data->c_red[a], "<<") == 0)
		{
			if(c2 == (count-1))
			{
				if (handle_heredoc2(data->c_red[++a], data, x) != 0)
					return (ERROR);
				c2++;
			}
			else
			{
				if (handle_heredoc1(data->c_red[++a], data, x) != 0)
					return (ERROR);
				c2++;
			}
		}
		else 
			a++;
	}
	return ((x->exit_status = 0));
}

int	handle_single_heredoc(t_token *current, t_extra *x)
{
	pid_t	pid;

	if (pipe(current->pi_doc) == -1)
		return ((perror("pipe")), ERROR);
	pid = fork();
	if (pid == 0)
	{
		signal_init_child();
		if (current->c_red)
		{
			if (process_heredoc(current, x, 0, 0) != 0)
				exit(ERROR);
		}
		exit(SUCCESS);
	}
	else if (pid)
		wait(&x->exit_status);
	close(current->pi_doc[1]);
	return (SUCCESS);
}

int	setup_heredoc(t_token *data, t_extra *x)
{
	t_token	*current;

	current = data;
	while (current)
	{
		if (has_heredoc(current->c_red))
		{
			if (handle_single_heredoc(current, x) != SUCCESS)
				return (ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}
