/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:02:14 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/04 23:22:21 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_validat_list(t_token **data, t_extra *x)
{
	t_token	*ptr;

	ptr = *data;
	while (ptr)
	{
		if (ptr->type == pipe_t)
		{
			if (ptr->prev == NULL || ptr->prev->type < 5)
				return (ft_put_error_tokens(1, 2, x), -1);
			if (ptr->next->type == end_t)
				return (ft_put_error_tokens(2, 2, x), -1);
			if ((0 < ptr->next->type && ptr->next->type < 5)
				&& ptr->next->next->type == end_t)
				return (ft_put_error_tokens(3, 2, x), -1);
		}
		else if (0 < ptr->type && ptr->type < 5)
		{
			if (ft_validat_list_2(ptr, x) == -1)
				return (-1);
		}
		ptr = ptr->next;
	}
	return (0);
}

int	ft_validat_list_2(t_token *ptr, t_extra *x)
{
	if (ptr->next->type == end_t)
		return (ft_put_error_tokens(3, 2, x), -1);
	if ((0 < ptr->next->type && ptr->next->type < 5))
	{
		if (ptr->next->type == append_t)
			return (ft_put_error_tokens(4, 2, x), -1);
		if (ptr->next->type == heredoc_t)
			return (ft_put_error_tokens(5, 2, x), -1);
		if (ptr->next->type == outfile_t)
			return (ft_put_error_tokens(6, 2, x), -1);
		if (ptr->next->type == infile_t)
			return (ft_put_error_tokens(7, 2, x), -1);
	}
	return (0);
}

void	ft_put_error_tokens(int f, int fd, t_extra *x)
{
	if (fd >= 0)
	{
		ft_putstr_fd(RED "Minishell: syntax error " RESET, 2);
		if (f == 0)
			ft_putstr_fd(RED "unclosed quotes\n" RESET, 2);
		else if (f == 1)
			ft_putstr_fd(RED "near unexpected token `|'\n" RESET, 2);
		else if (f == 2)
			ft_putstr_fd(RED "unexpected end of file\n" RESET, 2);
		else if (f == 3)
			ft_putstr_fd(RED "near unexpected token `newline'\n" RESET, 2);
		else if (f == 4)
			ft_putstr_fd(RED "near unexpected token `>>'\n" RESET, 2);
		else if (f == 5)
			ft_putstr_fd(RED "near unexpected token `<<'\n" RESET, 2);
		else if (f == 6)
			ft_putstr_fd(RED "near unexpected token `>'\n" RESET, 2);
		else if (f == 7)
			ft_putstr_fd(RED "near unexpected token `<'\n" RESET, 2);
		x->exit_status = 258;
	}
}
