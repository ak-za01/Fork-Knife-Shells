/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:24:46 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/26 21:15:30 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

void	free_temp_env(t_env *node)
{
	free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	print_env_node(t_env *node)
{
	printf("declare -x %s", node->name);
	if (node->value)
		printf("=\"%s\"", node->value);
	printf("\n");
}

void	copy_env_node(t_env *dest, t_env *src)
{
	dest->name = ft_strdup(src->name);
	if (src->value)
		dest->value = ft_strdup(src->value);
	else
		dest->value = NULL;
	dest->next = NULL;
}

void	insert_sorted(t_env **sorted_list, t_env *new_node)
{
	t_env	*current;

	if (!*sorted_list || ft_strcmp(new_node->name, (*sorted_list)->name) < 0)
	{
		new_node->next = *sorted_list;
		*sorted_list = new_node;
		return ;
	}
	current = *sorted_list;
	while (current->next && ft_strcmp(new_node->name, current->next->name) > 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
}

void	sort_env_list(t_env *env_list, t_env **copy)
{
	t_env	*current;
	t_env	*temp;

	current = env_list;
	while (current)
	{
		temp = malloc(sizeof(t_env));
		if (!temp)
			return ;
		copy_env_node(temp, current);
		insert_sorted(copy, temp);
		current = current->next;
	}
}
