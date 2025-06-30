/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 07:01:08 by noctis            #+#    #+#             */
/*   Updated: 2025/06/16 21:31:00 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

t_token_type	ft_get_token_type2(char *t, int f, int exp)
{
	if (!t)
		return (end_t);
	else if (ft_check_word("|", t) == 0 && exp == 0)
		return (pipe_t);
	else if (ft_check_word("<", t) == 0 && exp == 0)
		return (infile_t);
	else if (ft_check_word("<<", t) == 0 && exp == 0)
		return (heredoc_t);
	else if (ft_check_word(">", t) == 0 && exp == 0)
		return (outfile_t);
	else if (ft_check_word(">>", t) == 0 && exp == 0)
		return (append_t);
	else if (f == 1)
		return (string_t);
	else if (f == 2)
		return (cmd_arg_t);
	else if (ft_check_buildin_cmd(t) == 0)
		return (b_cmd_t);
	return (cmd_t);
}

void	ft_fix_cmd_pos_token2(t_token **data)
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
						ptr->type = ft_get_token_type2(ptr->value, 0, ptr->f);
						break ;
					}
					ptr = ptr->next;
				}
			}
		}
		ptr = ptr->next;
	}
}

void	ft_set_tokens_after_expanding(t_token **data)
{
	t_token	*ptr;
	int		f;

	if (!data)
		return ;
	ptr = *data;
	f = 0;
	while (ptr)
	{
		if (ptr->type == undefiend)
		{
			ptr->type = ft_get_token_type2(ptr->value, f, ptr->f);
			if (ptr->type == pipe_t)
				f = 0;
			else if (ptr->type == infile_t || ptr->type == heredoc_t
				|| ptr->type == outfile_t || ptr->type == append_t)
				f = 1;
			else
				f = 2;
		}
		else
			f = 2;
		ptr = ptr->next;
	}
	ft_fix_cmd_pos_token2(data);
}
