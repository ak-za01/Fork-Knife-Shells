/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 07:07:00 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/26 20:44:47 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

int	ft_tokenize(char *str, t_token **data, t_extra *x)
{
	if (ft_initialize_list(str, data) < 0)
		return (ft_put_error_tokens(0, 2, x), -1);
	ft_set_tokens_befor_expanding(data);
	if (ft_validat_list(data, x) < 0)
		return (-1);
	return (0);
}

int	ft_initialize_list(char *str, t_token **data)
{
	int		i;
	int		j;
	char	**t1;
	char	**t2;

	i = 0;
	t1 = ft_split2(str);
	if (!t1)
		return (-1);
	while (t1[i])
	{
		t2 = ft_split3(t1[i]);
		if (!t2)
			return (ft_free(t1), -1);
		j = 0;
		while (t2[j])
		{
			ft_add_list_end(data, ft_creat_new_list(t2[j], string_t));
			j++;
		}
		(ft_free(t2), i++);
	}
	ft_free(t1);
	ft_add_list_end(data, ft_creat_new_list(NULL, end_t));
	return (0);
}
