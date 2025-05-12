/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:33:44 by noctis            #+#    #+#             */
/*   Updated: 2025/05/12 12:33:09 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_toggle_quote(char **ptr, int *s_q, int *d_q)
{
	if (**ptr == '\'' && !(*d_q))
	{
		*s_q = !(*s_q);
		(*ptr)++;
		return (1);
	}
	if (**ptr == '"' && !(*s_q))
	{
		*d_q = !(*d_q);
		(*ptr)++;
		return (1);
	}
	return (0);
}

int	ft_calculs_exp_len(t_env *env_list, char *var)
{
	t_env	*env;

	env = env_list;
	while (env)
	{
		if (ft_strcmp(var, env->name) == 0)
		{
			return (ft_strlen(env->value));
		}
		env = env->next;
	}
	return (0);
}

int	ft_calcul_total_len(int s, char *ptr, t_env *env_list)
{
	char	*var;

	int (s_q), (d_q), f = 0;
	s_q = 0;
	d_q = 0;
	while (*ptr)
	{
		if (ft_toggle_quote(&ptr, &s_q, &d_q))
			continue ;
		if (*ptr == '$' && ft_check_ptr_value(*(ptr + 1), 0) && !s_q)
		{
			var = (ptr++, ft_get_expand_name(&ptr, &f));
			if (f == 1)
				s += ft_calcul_sepcial_len(var, env_list);
			else
				s += ft_calculs_exp_len(env_list, var);
			free(var);
		}
		else
		{
			s++;
			ptr++;
		}
	}
	return (s);
}

int	ft_calcul_var_len(char *ptr)
{
	int	s;

	s = 0;
	if (ft_check_ptr_value(*ptr, 1))
	{
		return (1);
	}
	else
	{
		while (ft_check_ptr_value(*ptr, 2))
		{
			s++;
			ptr++;
		}
	}
	return (s);
}

int	ft_calcul_sepcial_len(char *var, t_env *env_list)
{
	(void)var;
	(void)env_list;
	// if (ft_strcmp(var, "?") == 0)
	// {
	// extern int g_exit_status;
	// ft_putnbr(g_exit_status);
	// }
	return (0);
}
