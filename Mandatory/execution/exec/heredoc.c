/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:22:54 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/20 13:05:19 by anktiri          ###   ########.fr       */
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
		return (ERROR);
	a = 0;
	while (c_red[a])
	{
		if (ft_strcmp(c_red[a], "<<") == 0)
			return (ERROR);
		a++;
	}
	return (SUCCESS);
}

int	count_heredoc(t_token *data)
{
	int	i;
	int	count;

	i=0;
	count = 0;
	while (i < data->red_s)
	{
		if (ft_strcmp(data->c_red[i], "<<") == 0)
			count++;
		i++;
	}
	return (count);
}


// -----------------------------------------------------------------


// int	handle_heredoc(char *del, int *pipefd)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		// filter 1
// 		if (ft_strcmp(line, del) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		// filter 2
// 		ft_putstr_fd(line, pipefd[1]);
// 		ft_putstr_fd("\n", pipefd[1]);
// 		free(line);
// 	}
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	return (SUCCESS);
// }

// int	process_heredoc(t_token *data, t_extra *x)
// {
// 	int	a;

// 	a = 0;
// 	while (a < data->red_s)
// 	{
// 		if (ft_strcmp(data->c_red[a], "<<") == 0)
// 		{
// 			if (data->pi_doc[0] != -1)
// 				close(data->pi_doc[0]);
// 			if (handle_heredoc(data->c_red[++a], data->pi_doc) != 0)
// 				return (ERROR);
// 		}
// 		else
// 			a++;
// 	}
// 	return ((x->exit_status = 0));
// }

// int	setup_heredoc(t_token *data, t_extra *x)
// {
// 	t_token	*current;
// 	pid_t	pid;
// 	int		pipefd[2];

// 		if (pipe(pipefd) == -1)
// 			return ((perror("pipe")), ERROR);
// 	current = data;
// 	while (current)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			signal_init_child();
// 			if (current->c_red && has_heredoc(current->c_red))
// 			{
// 				if (process_heredoc(current, pipefd, x) != 0)
// 					exit(ERROR);
// 			}
// 			close(pipefd[0]);
// 			close(pipefd[1]);
// 			exit(SUCCESS);
// 		}
// 		else if (pid)
// 			wait(&x->exit_status);
// 		current->pi_doc = pipefd[0];
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		current = current->next;
// 	}
// 	return (SUCCESS);
// }


// -----------------------------------------------------------------

int	handle_heredoc1(char *del,t_token *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		// filter 1
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		// filter 2
		free(line);
	}
	return (SUCCESS);
}

int	handle_heredoc2(char *del,t_token *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		// filter 1
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		// filter 2
		ft_putstr_fd(line, data->pi_doc[1]);
		ft_putstr_fd("\n", data->pi_doc[1]);
		free(line);
	}
	close(data->pi_doc[0]);
	close(data->pi_doc[1]);
	return (SUCCESS);
}

int	process_heredoc(t_token *data, t_extra *x)
{
	int	a;
	int	c2;
	int count;

	a = 0;
	c2 = 0;
	count = count_heredoc(data);
	while (a < data->red_s)
	{	
		if (ft_strcmp(data->c_red[a], "<<") == 0)
		{
			if(c2 == (count-1))
			{
				if (handle_heredoc2(data->c_red[++a], data) != 0)
					return (ERROR);
				c2++;
			}
			else
			{
				if (handle_heredoc1(data->c_red[++a], data) != 0)
					return (ERROR);
				c2++;	
			}
		}
		else 
			a++;
	}
	return ((x->exit_status = 0));
}


int	setup_heredoc(t_token *data, t_extra *x)
{
	t_token	*current;
	pid_t	pid;

	current = data;
	while (current)
	{
		if(has_heredoc(current->c_red))
		{
			if (pipe(current->pi_doc) == -1)
				return ((perror("pipe")), ERROR);
			pid = fork();
			if (pid == 0)
			{
				signal_init_child();
				if (current->c_red )
				{
					if (process_heredoc(current, x) != 0)
						exit(ERROR);
				}
				exit(SUCCESS);
			}
			else if (pid)
				wait(&x->exit_status);
			close(current->pi_doc[1]);
		}
		current = current->next;
	}
	return (SUCCESS);
}

