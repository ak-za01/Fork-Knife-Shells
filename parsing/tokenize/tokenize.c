/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 07:07:00 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/24 21:36:18 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_tokenize(char *str, t_token **data)
{
	char	**t;

	if (ft_initialize_list(str, data) < 0)
		return (ft_put_error("minishell: syntax error: unclosed quotes\n", 2), -1);
	ft_set_tokens(data);
	if (ft_validat_list(data) < 0)
		return (-1);
	
		
	// fix cmd token like " > out ls"		
	// fix cmd token like " < in  ls"	
		
	return (0);
}

int	ft_initialize_list(char *str, t_token **data)
{
	int		i;
	int		j;
	char	**t1;
	char	**t2;

	i = 0;
	t1 = ft_split2(str, ' ');
	if (!t1)
		return (-1);
	while (t1[i])
	{
		t2 = ft_split3(t1[i]);
		if (!t2)
			return (ft_free(t1), -1);
		j = 0;
		while (t2[j])
		{
			ft_add_list_end(data, ft_creat_new_list(t2[j], string_t));
			j++;
		}
		(ft_free(t2),i++) ;
	}
	ft_free(t1);
	ft_add_list_end(data, ft_creat_new_list(NULL, end_t));
	return (0);
}

void	ft_set_tokens(t_token **data)
{
	t_token	*ptr;
	int		f;

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
	if (ft_check_word("echo", t) == 0)
		return (0);
	else if (ft_check_word("cd", t) == 0)
		return (0);
	else if (ft_check_word("pwd", t) == 0)
		return (0);
	else if (ft_check_word("export", t) == 0)
		return (0);
	else if (ft_check_word("unset", t) == 0)
		return (0);
	else if (ft_check_word("exit", t) == 0)
		return (0);
	return (-1);
}

int	ft_check_word(char *t1, char *t2)
{
	if (ft_strnstr(t1, t2, ft_strlen(t2)) != NULL
		&& (ft_strlen(t1) == ft_strlen(t2)))
		return (0);
	return (-1);
}

int	ft_validat_list(t_token **data)
{
	t_token	*ptr;

	ptr = *data;
	while (ptr)
	{	
		if(ptr->type == pipe_t)
		{
			if (ptr->prev==NULL || ptr->prev->type <5  )
			{
				 return (ft_put_error(RED"minishell: syntax error near unexpected token `|'\n"RESET, 2), -1);
			}
			if (ptr->next->type == end_t)
			{
				 return (ft_put_error(RED"minishell: syntax error: unexpected end of file\n"RESET, 2), -1);
			}
			if((0< ptr->next->type && ptr->next->type <5 )&& ptr->next->next->type == end_t  )
			{
				 return (ft_put_error(RED"minishell: syntax error near unexpected token `newline'\n"RESET, 2), -1);
			}
		}
		else if(0< ptr->type  && ptr->type <5)
		{
			if(ptr->next->type == end_t)
			{
				 return (ft_put_error(RED"minishell: syntax error near unexpected token `newline'\n"RESET, 2), -1);
			}
			if((0< ptr->next->type && ptr->next->type <5 ))
			{
				if (ptr->next->type == append_t)
				 return (ft_put_error(RED"minishell: syntax error near unexpected token `>>'\n"RESET, 2), -1);
				if (ptr->next->type == heredoc_t)
				 return (ft_put_error(RED"minishell: syntax error near unexpected token `<<'\n"RESET, 2), -1);
				if (ptr->next->type == outfile_t)
				 return (ft_put_error(RED"minishell: syntax error near unexpected token `>'\n"RESET, 2), -1);
				if (ptr->next->type == infile_t)
				 return (ft_put_error(RED"minishell: syntax error near unexpected token `<'\n"RESET, 2), -1);
			}
		}
		ptr = ptr->next;
	}
	return (0);
}
