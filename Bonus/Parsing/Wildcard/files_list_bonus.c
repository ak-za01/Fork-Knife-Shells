/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_list_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:05:31 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/16 21:32:17 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

int	ft_is_hidden(t_wc *data)
{
	if (!data || !data->value)
		return (-1);
	if (data->value[0] == '.')
		return (1);
	return (0);
}

int	ft_get_wc_list_size(const char *cwd, int f)
{
	DIR				*dir;
	struct dirent	*key;
	int				count;

	count = 0;
	dir = opendir(cwd);
	if (!dir)
		return (-1);
	while (1)
	{
		key = readdir(dir);
		if (!key)
			break ;
		if (f == 1 && key->d_name[0] == '.')
			count++;
		else if (f == 0 && key->d_name[0] != '.')
			count++;
	}
	closedir(dir);
	return (count);
}

int	ft_copy_wc_string(char **t, int *i, char *str)
{
	t[*i] = ft_strdup(str);
	if (!t[*i])
		return (-1);
	(*i)++;
	return (0);
}

int	ft_get_wc_list_filled(char **t, const char *cwd, int f)
{
	int				i;
	DIR				*dir;
	struct dirent	*key;

	i = 0;
	dir = opendir(cwd);
	if (!dir)
		return (-1);
	while (1)
	{
		key = readdir(dir);
		if (!key)
			break ;
		if (f == 1 && key->d_name[0] == '.')
		{
			if (ft_copy_wc_string(t, &i, key->d_name) < 0)
				return (closedir(dir), -1);
		}
		else if (f == 0 && key->d_name[0] != '.')
		{
			if (ft_copy_wc_string(t, &i, key->d_name) < 0)
				return (closedir(dir), -1);
		}
	}
	return (t[i] = NULL, closedir(dir), 0);
}

char	**ft_files_list(const char *cwd, t_wc *data)
{
	int		s;
	int		f;
	char	**t;

	f = ft_is_hidden(data);
	s = ft_get_wc_list_size(cwd, f);
	if (s == -1)
		return (NULL);
	t = malloc((s + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	if (ft_get_wc_list_filled(t, cwd, f) == -1)
		return (ft_free(t), NULL);
	ft_sort_wc_list_final(t);
	return (t);
}
