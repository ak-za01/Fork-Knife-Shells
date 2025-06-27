/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:02:17 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/26 20:41:45 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

void	ft_set_tokens_befor_expanding(t_token **data)
{
	t_token	*ptr;
	int		f;

	if (!data)
		return ;
	ptr = *data;
	f = 0;
	while (ptr)
	{
		ptr->type = ft_get_token_type(ptr->value, f);
		if (ptr->type == pipe_t)
			f = 0;
		else if (ptr->type == infile_t || ptr->type == heredoc_t
			|| ptr->type == outfile_t || ptr->type == append_t)
			f = 1;
		else
			f = 2;
		ptr = ptr->next;
	}
	ft_fix_cmd_pos_token(data);
}

void	ft_fix_cmd_pos_token(t_token **data)
{
	t_token	*ptr;

	ptr = *data;
	while (ptr && ptr->next)
	{
		if (ptr->type == infile_t || ptr->type == heredoc_t
			|| ptr->type == outfile_t || ptr->type == append_t)
		{
			if (ptr->prev == NULL || (ptr->prev && ptr->prev->type == pipe_t))
			{
				while (ptr->next && ptr->type != pipe_t && ptr->type != end_t)
				{
					if (ptr->type == cmd_t || ptr->type == b_cmd_t)
						break ;
					else if (ptr->type == cmd_arg_t)
					{
						ptr->type = ft_get_token_type(ptr->value, 0);
						break ;
					}
					ptr = ptr->next;
				}
			}
		}
		ptr = ptr->next;
	}
}

t_token_type	ft_get_token_type(char *t, int f)
{
	if (!t)
		return (end_t);
	else if (ft_check_word("|", t) == 0)
		return (pipe_t);
	else if (ft_check_word("<", t) == 0)
		return (infile_t);
	else if (ft_check_word("<<", t) == 0)
		return (heredoc_t);
	else if (ft_check_word(">", t) == 0)
		return (outfile_t);
	else if (ft_check_word(">>", t) == 0)
		return (append_t);
	else if (f == 1)
		return (string_t);
	else if (f == 2)
		return (cmd_arg_t);
	else if (ft_check_buildin_cmd(t) == 0)
		return (b_cmd_t);
	return (cmd_t);
}

int	ft_check_buildin_cmd(char *t)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strdup(t);
	if (!tmp1)
		return (-1);
	tmp2 = ft_remove_q(tmp1);
	if (!tmp1)
		return (free(tmp1), -1);
	if (ft_check_word("echo", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("cd", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("pwd", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("export", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("unset", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("env", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("exit", tmp2) == 0)
		return (free(tmp2), 0);
	return (free(tmp2), -1);
}

int	ft_check_word(char *t1, char *t2)
{
	if (ft_strnstr(t1, t2, ft_strlen(t2)) != NULL
		&& (ft_strlen(t1) == ft_strlen(t2)))
		return (0);
	return (-1);
}
