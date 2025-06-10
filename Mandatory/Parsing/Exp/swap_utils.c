/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:41:11 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/09 18:56:56 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_toggle_quote(char **ptr, int *s_q, int *d_q)
{
	if (**ptr == '\'' && !(*d_q))
	{
		*s_q = !(*s_q);
	}
	if (**ptr == '"' && !(*s_q))
	{
		*d_q = !(*d_q);
	}
	return (0);
}

int	ft_calcul_total_len(int s, char *ptr, t_extra *x, int f)
{
	int (s_q), d_q = 0;
	s_q = 0;
	while (*ptr)
	{
		ft_toggle_quote(&ptr, &s_q, &d_q);
		if (*ptr == '$' && ft_check_ptr_value(*(ptr + 1), 0) && !s_q)
		{
			if (ft_calcul_total_len_fix_norm(x, f, &s, &ptr) == -1)
				return (-1);
		}
		else
		{
			s++;
			ptr++;
		}
	}
	return (s);
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

int	ft_calcul_sepcial_len(char *var, t_extra *x)
{
	char	*tmp;
	int		s;

	s = 0;
	if (ft_strcmp(var, "?") == 0)
	{
		tmp = ft_itoa(x->exit_status);
		if (!tmp)
			return (-1);
		s = ft_strlen(tmp);
		free(tmp);
		return (s);
	}
	return (0);
}
