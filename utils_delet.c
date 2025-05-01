/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_delet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:49:05 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/01 18:42:58 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"
#include "./include/parse.h"

void	leaks(void)
{
	system("leaks -q Minishell");
}

// ----------------------------------------------------

static void	ft_print_tab2(char **arr, const char *label)
{
	int	i;

	printf("\t" CYAN "%-8s:" RESET " ", label);
	if (!arr || !arr[0])
	{
		printf(YELLOW "None\n" RESET);
		return ;
	}
	i = 0;
	while (arr[i])
	{
		printf("%s", arr[i]);
		if (arr[i + 1])
			printf(YELLOW " | " RESET);
		i++;
	}
	printf("\n");
}

void	ft_print_list(t_token *data)
{
	int	index;

	index = 0;
	printf(RED "           Linked List Contents             \n" RESET);
	if (!data)
	{
		printf("\t[Empty List]\n");
		return ;
	}
	while (data)
	{
		printf(RED "Node %d:\n" RESET, index++);
		if (data->value)
			printf(" \t" CYAN "%-8s:" RESET " %s\n", "CMD", data->value);
		else
			printf(" \t" CYAN "%-8s:" RESET " " YELLOW "None" RESET "\n",
				"CMD");
		printf("\t" CYAN "%-8s:" RESET " %d\n", "Token", data->type);
		ft_print_tab2(data->c_arg, "Args");
		ft_print_tab2(data->c_red, "Redirs");
		printf("\n");
		data = data->next;
	}
	printf(RED "               End of List                 \n" RESET);
}

// ----------------------------------------------------

void	ft_print_list1(t_token *data)
{
	if (!data)
	{
		ft_printf("nothing\n");
		return ;
	}
	ft_printf("\n----------------\n");
	while (data)
	{
		ft_printf(" %s ", data->value);
		data = data->next;
	}
	ft_printf("\n----------------\n");
}

// ----------------------------------------------------

void	ft_print_tab(char **t)
{
	int	i;

	i = 0;
	if (!t)
		return ;
	while (t[i])
	{
		ft_printf("\n\t\t > %s <\n", t[i]);
		i++;
	}
}

// ----------------------------------------------------
