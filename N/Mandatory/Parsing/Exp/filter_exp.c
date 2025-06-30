/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:32:42 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/30 20:59:18 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

char	*ft_filter_exp(t_extra *x, char *str, int f1, int f2)
{
	char	**t;
	char	*tmp;

	int (s), i = 0;
	t = ft_split4(str);
	if (!t)
		return (NULL);
	s = ft_strlen_2(t);
	while (t[i])
	{
		// printf("> we are in %d : %s <\n", i + 1, t[i]);
		f1 = ft_check_q_status(t[i]);
		f2 = ft_check_dollar(t[i]);
		tmp = ft_strdup(t[i]);
		if (!tmp)
			return (ft_free2(t, s), NULL);
		if (f2 == 1)
		{
			// printf("> dollar in %d : %s <\n", i + 1, t[i]);
			free(t[i]);
			t[i] = NULL;
			t[i] = ft_swap_value(0, tmp, x, 0);
			if (!t[i])
				return (ft_free2(t, s), NULL);
			// if (f1 != 0)
			// {
			// 	t[i] = ft_remove_q(t[i]);
			// 	if (!t[i])
			// 		return (ft_free2(t, s), NULL);
			// }
		}
		else
		{
			// printf("> no dollar in %d : %s <\n", i + 1, t[i]);
			t[i] = ft_remove_q(t[i]);
			if (!t[i])
				return (ft_free2(t, s), NULL);
		}
		free(tmp);
        	// printf("> end result  %d : %s <\n", i + 1, t[i]);
		i++;
	}
	return (ft_strjoin4(t));
}
