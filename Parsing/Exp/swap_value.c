/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:23:53 by noctis            #+#    #+#             */
/*   Updated: 2025/05/12 12:32:36 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

char	*ft_swap_value(int i, char *ptr, t_extra *x)
{
	char	*var;
	char	*t;

	int (s_q), (d_q), f = 0;
	s_q = 0;
	d_q = 0;
	t = malloc(ft_calcul_total_len(0, ptr, x->env_list) + 1);
	if (!t)
		return (NULL);
	while (*ptr)
	{
		if (ft_toggle_quote(&ptr, &s_q, &d_q))
			continue ;
		if (*ptr == '$' && ft_check_ptr_value(*(ptr + 1), 0) && !s_q)
		{
			var = (ptr++, ft_get_expand_name(&ptr, &f));
			if (f == 1)
				(ft_handle_special_char(x->env_list, var, t, &i), free(var));
			else
				(ft_copy_exp_value(x->env_list, var, t, &i), free(var));
		}
		else
			t[i++] = *(ptr++);
	}
	return (t[i] = '\0', t);
}

int	ft_check_ptr_value(char c, int f)
{
	if (f == 0)
	{
		if (c && (c == '?' || c == '@' || c == '_' || ft_isalnum(c)))
			return (1);
	}
	if (f == 1)
	{
		if (c && (c == '?' || c == '@' || ft_isdigit(c)))
			return (1);
	}
	else if (f == 2)
	{
		if (c && (ft_isalnum(c) || c == '_'))
			return (1);
	}
	return (0);
}

char	*ft_get_expand_name(char **ptr, int *f)
{
	char	*var;
	int		j;

	j = 0;
	var = malloc(ft_calcul_var_len(*ptr) + 1);
	if (!var)
		return (NULL);
	if (ft_check_ptr_value(**ptr, 1))
	{
		var[j++] = *(*ptr)++;
		*f = 1;
	}
	else
	{
		while (ft_check_ptr_value(**ptr, 2))
			var[j++] = *(*ptr)++;
	}
	var[j] = '\0';
	return (var);
}

void	ft_copy_exp_value(t_env *env_list, char *var, char *t, int *i)
{
	t_env	*env;
	int		j;

	env = env_list;
	while (env)
	{
		if (ft_strcmp(var, env->name) == 0)
		{
			j = 0;
			while (env->value[j])
			{
				t[*i] = env->value[j];
				j++;
				(*i)++;
			}
			break ;
		}
		env = env->next;
	}
}

void	ft_handle_special_char(t_env *env_list, char *var, char *t, int *i)
{
	(void)var;
	(void)t;
	(void)i;
	(void)env_list;
	// if (ft_strcmp(var, "?") == 0)
	// {
	// 	// extern int g_exit_status;
	// 	// ft_putnbr(g_exit_status);
	// }
	return ;
}
