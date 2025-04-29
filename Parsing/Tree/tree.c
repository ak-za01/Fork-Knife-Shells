/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 05:09:22 by noctis            #+#    #+#             */
/*   Updated: 2025/04/29 02:03:16 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

t_ast *build_tree(t_token *start, t_token *end)
{
// 	t_token *ptr = start;
// 	t_ast *node;

// 	while (ptr != end)
// 	{
// 		if (ptr->type == pipe_t)
// 		{
// 			node = malloc(sizeof(t_ast));
// 			node->value = ft_strdup();
// 			node->type = 0;
// 			node->c_arg = NULL;
// 			node->c_red = NULL;
// 			node->left = build_ast(start, ptr);
// 			node->right = build_ast(ptr->next, end);
// 			return node;
// 		}
// 		ptr = ptr->next;
// 	}
// 	node = malloc(sizeof(t_ast));
// 	node->value = ft_strdup();
// 	node->type = 1;
// 	node->c_arg = start->c_arg;
// 	node->c_red = start->c_red;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return node;
}

int ft_tree(t_token **data, t_ast **tree)
{
    if(!data || !*data)
        return -1;

    t_token *start;
    t_token *end;

    start=*data;
    end=ft_last_list(*data);
    
    *tree=build_tree(start, end);
    if(!tree)
        return -1;
    return 0;    
}
