/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 07:07:00 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/09 21:25:46 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_tokenize(char *str, t_token **data)
{
	char	**t;

	ft_initialize_list(str, data);
	ft_set_tokens(data);
	if(ft_validat_list(data)<0)
		return (-1);
    
	return (0);
}


int	ft_initialize_list(char *str, t_token **data)
{
	int				i;
	int				j;
	char			**t1;
	char			**t2;

	i = 0;
    t1 = ft_split2(str, ' ');
	if (!t1)
		return (-1);
	while (t1[i])
	{
		t2 = ft_split3(t1[i]);
        if(!t2)
            return -1;
		j = 0;
		while (t2[j])
		{
			ft_add_list_end(data, ft_creat_new_list(t2[j], string_t));
			j++;
		}
		ft_free(t2);
		i++;
	}
 	ft_free(t1);   
	ft_add_list_end(data, ft_creat_new_list(NULL, end_t));
    return 0;
}

void  ft_set_tokens(t_token **data)
{
	t_token *ptr;
	ptr=*data;
	int f=0;
	while(ptr)
	{
       ptr->type=ft_get_token_type(ptr->value, f);
    
        if( ptr->type== pipe_t )
            f=0;
        else if(  ptr->type== infile_t || ptr->type== heredoc_t || ptr->type== outfile_t || ptr->type== append_t)
            f=1;
        else 
            f=2;
		ptr=ptr->next;
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

int  ft_validat_list(t_token **data)
{
	t_token *ptr;
	ptr=*data;
	int i=0;
	while(ptr)
	{
        if( ptr->type <5 && ptr->next->type < 5 )
            return -1;
		if( ptr->type <5 && ptr->next->type == 9 )
			return -1;
		if( ptr->type == 0 && i==0 )
			return -1;

		i++;
		ptr=ptr->next;
	}
	return 0;
}