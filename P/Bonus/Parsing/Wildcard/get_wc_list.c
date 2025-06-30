/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 00:59:49 by noctis            #+#    #+#             */
/*   Updated: 2025/06/16 16:19:29 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

void	ft_sort_wc_list_final(char **t)
{
	int		i;
	int		s;
	char	*tmp;

	s = ft_strlen_2(t);
	while (s >= 0)
	{
		i = 1;
		while (i < s)
		{
			if (ft_strcmp(t[i], t[i - 1]) < 0)
			{
				tmp = t[i];
				t[i] = t[i - 1];
				t[i - 1] = tmp;
			}
			i++;
		}
		s--;
	}
}

char	**ft_get_wc_list(char *str)
{
	char	**t1;
	t_wc	*t2;
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	t2 = NULL;
	if (ft_cmd_list(str, &t2) < 0)
		return (NULL);
	t1 = ft_files_list(cwd, t2);
	if (!t1)
		return (ft_free_list2(&t2), NULL);
	t1 = ft_filter_wc_list(t1, t2, 0, 0);
	if (!t1)
		return (ft_free_list2(&t2), NULL);
	ft_sort_wc_list_final(t1);
	return (ft_free_list2(&t2), t1);
}
