/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:15:07 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/05 16:24:40 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/parse.h"

void ft_parse(char *str)
{
    t_token *data;
    data=NULL;
    
    ft_tokenize(str,&data);    

   

    ft_print_list(data);
    ft_free_list(&data);
}