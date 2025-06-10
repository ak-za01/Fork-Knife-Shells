/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:26:33 by noctis            #+#    #+#             */
/*   Updated: 2025/06/10 01:28:57 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/main.h"
#include "../../include/parse.h"

int ft_check_wc_string(char *t)
{
    int i=0;
    while(t[i] || t[i]=='\\')
    {
        if(t[i] == '*')
            return 1;
        i++;
    }
    return 0;
}

int ft_expanding_wc(t_token **data, t_extra *x)
{
    char **t;
    t_token *ptr;
    t_token *next;
    int f;
    
    ptr=*data;
    while(ptr && ft_check_wc_string(ptr->value))
    {
        if(ptr->prev && ptr->prev->type==heredoc_t)
        {
            ptr=ptr->next;
            // continue;
        }
        else
        {
            next=ptr->next;
            f=ft_get_wc_list(ptr->value,x,t);
            if(f==-1)
                return -1;
       
            // ft_sort_wc_list(t);
            // if(ft_add_wc_content(ptr,data,x)==-1)
            //     return -1;
            ptr=next;             
        }
    }
    return 0;
}

int ft_wildcard(t_token **data, t_extra *x)
{
	if (ft_expanding_wc(data, x) < 0)
		return (-1);
	// if (ft_fix_list(data) < 0)
	// 	return (-1);
	// if (ft_re_tokenizing(data) < 0)
	// 	return (-1);
    
    return 0;
}