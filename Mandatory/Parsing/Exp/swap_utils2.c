/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:28:59 by aakritah          #+#    #+#             */
/*   Updated: 2025/07/01 13:33:22 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_swap_value_fix_norm(int f, t_extra *x, t_norm *n_data, int *i)
{
	if (f == 1)
	{
		if (ft_handle_special_char(x, n_data->var, n_data->t, i) == -1)
			return (-1);
	}
	else
		(ft_copy_exp_value(x->env_list, n_data->var, n_data->t, i));
	return (0);
}

int	ft_calcul_total_len_fix_norm(t_extra *x, int f, int *s, char **ptr)
{
	char	*var;
	int		k;

	var = ((*ptr)++, ft_get_expand_name(ptr, &f));
	if (!var)
		return (-1);
	if (f == 1)
	{
		k = ft_calcul_sepcial_len(var, x);
		if (k == -1)
			return (-1);
		(*s) += k;
	}
	else
		(*s) += ft_calculs_exp_len(x->env_list, var);
	free(var);
	return (0);
}

int	ft_check_ptr_status(char *ptr, int s_q, int d_q)
{
	if (s_q == 1 || d_q == 1)
	{
		if (*ptr == '\'' || *ptr == '\"')
			return (0);
	}
	else
	{
		if (*ptr == '\0')
			return (0);
	}
	return (1);
}
