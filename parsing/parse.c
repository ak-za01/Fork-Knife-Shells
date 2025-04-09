/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:15:07 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/09 21:22:35 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/parse.h"

void ft_parse(char *str)
{
    t_token *data;
    data=NULL;
    
    if(ft_tokenize(str,&data)<0)
    {
        printf("\n---------\n");
        printf("Error");
        printf("\n---------\n");
        ft_free_list(&data); 
        return ;   
    }

   

    ft_print_list(data);
    ft_free_list(&data);
}