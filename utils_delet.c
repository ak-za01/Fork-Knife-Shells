/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_delet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:49:05 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/12 12:37:09 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"
#include "./include/parse.h"

void	leaks(void)
{
	system("leaks -q Minishell");
}

// ----------------------------------------------------

static void	ft_print_tab2(int s, char **arr, const char *label)
{
	int	i;

	printf("\t" CYAN "%-8s:" RESET " ", label);
	if (!arr || !arr[0])
	{
		printf(YELLOW "None\n" RESET);
		return ;
	}
	i = 0;
	while (i < s)
	{
		printf("%s", arr[i]);
		if (i + 1 < s)
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
		printf("\t" CYAN "%-8s:" RESET " %d\n", "expand", data->f);
		ft_print_tab2(data->arg_s, data->c_arg, "Args");
		ft_print_tab2(data->red_s, data->c_red, "Redirs");
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
