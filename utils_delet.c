/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_delet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:49:05 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/28 23:15:26 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"
#include "./include/parse.h"

void	leaks(void)
{
	system("leaks -q Minishell");
}

void	ft_print_list(t_token *data)
{
	ft_printf(RED "\n Printf list data :\n\n" RESET);
	if (!data)
	{
		ft_printf("nothing\n");
		return ;
	}
	while (data)
	{
		// if(data->value)
			ft_printf("\tCMD : %s", data->value);
		ft_printf(RED "  -|-  " RESET);
		ft_printf("Token : %d", data->type);
		ft_printf(RED "  -|-  " RESET);
		// ft_printf("Precd : %d", data->prec);
		// ft_printf(RED "  -|-  " RESET);
		ft_printf("\n \t arg : \n");
		print_tab(data->c_arg);
		ft_printf("\n \t red : \n");
		print_tab(data->c_red);
		ft_printf("\n\n");
		data = data->next;
	}
	ft_printf(RED " > done <\n" RESET);
}

void	ft_print_list2(t_token *data)
{
	if (!data)
	{
		ft_printf("\t\tnothing\n");
		return ;
	}
	while (data)
	{
		ft_printf("\t\tCMD : %s", data->value);
		ft_printf(RED "  -|-  " RESET);
		ft_printf("Token : %d", data->type);
		ft_printf(RED "  -|-  " RESET);
		ft_printf("Precd : %d", data->prec);
		ft_printf(RED "  -|-  " RESET);
		ft_printf("\n \t\t arg : \n");
		ft_printf("\n\n", data->prec);
		data = data->next;
	}
}

void	ft_print_list3(t_token *data)
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

void	print_tab(char **t)
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
