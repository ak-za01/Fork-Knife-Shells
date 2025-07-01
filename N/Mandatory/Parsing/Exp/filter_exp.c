/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:32:42 by aakritah          #+#    #+#             */
/*   Updated: 2025/07/01 06:39:47 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

char	*ft_marque_q(char *t)
{
	int		s;
	char	*t2;
	int		i;
	int		j;

	s = ft_strlen(t);
	t2 = malloc(s + 3);
	if (!t2)
		return (NULL);
	i = 0;
	j = 0;
	while (t[i])
	{
		if (j == 1 || j == s)
		{
			t2[j] = '\x1F';
			j++;
		}
		t2[j] = t[i];
		i++;
		j++;
	}
	t2[j] = '\0';
	return (t2);
}

char	*ft_process_dollar(char **t, int i, t_extra *x, char *tmp)
{
	int		f1;
	char	*new_val;

	f1 = ft_check_q_status(t[i]);
	free(t[i]);
	t[i] = NULL;
	t[i] = ft_swap_value(0, tmp, x, 0);
	if (!t[i])
		return (NULL);
	if (f1 != 0)
	{
		new_val = ft_marque_q(t[i]);
		if (!new_val)
			return (free(t[i]), t[i] = NULL, NULL);
		free(t[i]);
		t[i] = new_val;
	}
	return (t[i]);
}

char	*ft_process_token(char **t, int i, t_extra *x, int f2)
{
	char	*tmp;

	tmp = ft_strdup(t[i]);
	if (!tmp)
		return (NULL);
	if (f2 == 1)
	{
		if (!ft_process_dollar(t, i, x, tmp))
			return (free(tmp), NULL);
	}
	else
	{
		t[i] = ft_remove_q(t[i]);
		if (!t[i])
			return (free(tmp), NULL);
	}
	free(tmp);
	return (t[i]);
}

char	*ft_filter_exp(t_extra *x, char *str, int f1, int f2)
{
	char	**t;
	int		s;
	int		i;
	char	*tmp;

	i = 0;
	t = ft_split4(str);
	if (!t)
		return (NULL);
	s = ft_strlen_2(t);
	while (t[i])
	{
		f2 = ft_check_dollar(t[i]);
		if (!ft_process_token(t, i, x, f2))
			return (ft_free2(t, s), NULL);
		i++;
	}
	tmp = ft_strjoin4(t);
	if (!tmp)
		return (ft_free2(t, s), NULL);
	return (ft_free2(t, s), tmp);
}
