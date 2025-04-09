/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 07:10:20 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/04 08:14:02 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

t_token *ft_creat_new_list(char *str, t_token_type type)
{
    t_token *n;
    
    n=malloc(sizeof(t_token));
    if(!n)
        return NULL;
    if(!str)
        n->value=NULL;
    else
        n->value=ft_strdup(str);
    n->type=type;
    n->next=NULL;
    n->prev=NULL;
    return n;
}

void ft_add_list_front(t_token **data, t_token *n)
{
    if (!data)
		return ;
	if (!*data)
	{
		*data = n;
		return ;
	}
    (*data)->prev=n;
    n->next=(*data);
    (*data)=n;
     return;
}

void ft_add_list_end(t_token **data, t_token *n)
{
    t_token *ptr;

    if (!data)
		return ;
	if (!*data)
	{
		*data = n;
		return ;
	}
    ptr=(*data);
    while(ptr->next)
        ptr=ptr->next;
    ptr->next=n;
    n->prev=ptr;
    return;
}

void ft_free_list(t_token **data)
{
    if(!data)
        return;
    t_token *ptr;
    
    while(*data)
    {
        ptr=(*data);
        (*data)=(*data)->next;
        free(ptr->value);
        free(ptr);
    }
}

