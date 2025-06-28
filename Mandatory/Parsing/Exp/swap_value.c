/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:41:18 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/27 21:29:33 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

char	*ft_swap_value(int i, char *ptr, t_extra *x, int f)
{
	t_norm	n_data;

	int (s), (s_q), d_q = 0;
	s_q = 0;
	s = ft_calcul_total_len(0, ptr, x, 0);
	n_data.t = malloc(s + 1);
	if (s == -1 || !n_data.t)
		return (free(n_data.t), NULL);
	while (*ptr)
	{
		ft_toggle_quote(&ptr, &s_q, &d_q);
		if (*ptr == '$' && ft_check_ptr_status(ptr + 1, s_q, d_q)
			&& ft_check_ptr_value(*(ptr + 1), 0) && !s_q)
		{
			n_data.var = (ptr++, ft_get_expand_name(&ptr, &f));
			if (!n_data.var)
				return (NULL);
			if (ft_swap_value_fix_norm(f, x, &n_data, &i) == -1)
				return (free(n_data.var), NULL);
			free(n_data.var);
		}
		else
			n_data.t[i++] = *(ptr++);
	}
	return (n_data.t[i] = '\0', n_data.t);
}

int	ft_check_ptr_value(char c, int f)
{
	if (f == 0)
	{
		if (c && (c == '?' || c == '@' || c == '\"' || c == '\'' || c == '_'
				|| ft_isalnum(c)))
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
		*f = 0;
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
			if (!env->value)
				break ;
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

int	ft_handle_special_char(t_extra *x, char *var, char *t, int *i)
{
	char	*tmp;
	int		s;

	s = 0;
	if (ft_strcmp(var, "?") == 0)
	{
		tmp = ft_itoa(x->exit_status);
		if (!tmp)
			return (-1);
		while (tmp[s])
		{
			t[*i] = tmp[s];
			s++;
			(*i)++;
		}
		free(tmp);
	}
	return (0);
}
