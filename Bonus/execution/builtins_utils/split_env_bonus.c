/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:44:05 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/26 21:15:27 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

static char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;
	size_t	i;

	dest = malloc((n + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	ft_free_split(char **result, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

char	**ft_split_env(char const *s, char c)
{
	char	**result;
	char	*delim;
	size_t	key_len;

	if (!s)
		return (NULL);
	result = malloc(3 * sizeof(char *));
	if (!result)
		return (NULL);
	delim = ft_strchr(s, c);
	if (!delim)
	{
		result[0] = ft_strndup(s, ft_strlen(s));
		result[1] = NULL;
		if (!result[0])
			return (ft_free_split(result, 0), NULL);
		return (result);
	}
	key_len = delim - s;
	result[0] = ft_strndup(s, key_len);
	result[1] = ft_strndup(delim + 1, strlen(delim + 1));
	if (!result[0] || !result[1])
		return (ft_free_split(result, 2), NULL);
	result[2] = NULL;
	return (result);
}

void	free_env_list(t_extra *x)
{
	t_env	*ptr;
	t_env	*tmp;

	ptr = x->env_list;
	if (!ptr)
		return ;
	while (ptr)
	{
		tmp = (ptr);
		(ptr) = (ptr)->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	return ;
}
