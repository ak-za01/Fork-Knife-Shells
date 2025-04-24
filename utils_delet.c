/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_delet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:49:05 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/24 21:16:08 by aakritah         ###   ########.fr       */
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
		ft_printf( "\tCMD : %s", data->value);
		ft_printf(RED "  -|-  " RESET);
		ft_printf( "Token : %d", data->type);
		ft_printf(RED "  -|-  " RESET);
		ft_printf( "Precd : %d\n\n", data->prec);
		data = data->next;
	}
	ft_printf(RED" > done <\n"RESET);
}

void	ft_print_list2(t_token *data)
{
	FILE *fd = fopen("./test/out.txt", "w+");
	if (!fd)
		return ;
	fprintf(fd,"----------------\n");
	while (data)
	{
		fprintf(fd, "cmd : %s , token : %d , precd : %d\n", data->value, data->type, data->prec);
		fprintf(fd,"----------------\n");
		data = data->next;
	}
	fclose(fd);
	ft_printf("\n");
}

void	ft_print_list3(t_token *data)
{
	if (!data)
	{
		ft_printf("nothing\n");
		return ;
	}
	ft_printf("\n----------------\n");
	while (data->next)
	{
		ft_printf( " %s ", data->value);
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
	ft_printf("----------------\n");
	while (t[i])
	{
		ft_printf("> %s <\n", t[i]);
		i++;
	}
	ft_printf("----------------\n");
}
