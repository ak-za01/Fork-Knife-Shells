/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:01:02 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/26 21:19:42 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

int	has_heredoc(char **c_red)
{
	int	a;

	if (!c_red)
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

	i = 0;
	count = 0;
	while (i < data->red_s)
	{
		if (data->c_red[i] && ft_strcmp(data->c_red[i], "<<") == 0)
			count++;
		i++;
	}
	return (count);
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
		return (free(t1), free(t2), f2);
	}
}

int	check_signal(t_token *data, char *line, int f)
{
	if (f)
	{
		if (g_signal_received == SIGINT)
		{
			if (line)
				free(line);
			g_signal_received = 0;
			close(data->pi_doc[0]);
			close(data->pi_doc[1]);
			return (1);
		}
	}
	else
	{
		if (g_signal_received == SIGINT)
		{
			if (line)
				free(line);
			g_signal_received = 0;
			return (1);
		}
	}
	return (0);
}
