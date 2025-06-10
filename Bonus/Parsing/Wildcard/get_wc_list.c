/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 00:59:49 by noctis            #+#    #+#             */
/*   Updated: 2025/06/10 01:41:25 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_get_wc_list_size(const char *cwd)
{
	DIR				*dir;
	struct dirent	*key;
	int				count;

	count = 0;
	dir = opendir(cwd);
	if (!dir)
		return (-1);
	while ((key = readdir(dir)))
		count++;
	closedir(dir);
	return (count);
}

int ft_get_wc_list_filled(char **t, int s,const  char *cwd)
{
    int i;
	DIR				*dir;
	struct dirent	*key;
    
    i=0;
    dir=opendir(cwd);
    if(!dir)
        return -1;
    while((key = readdir(dir)))
    {
        t[i]=ft_strdup(key->d_name);
        if(!t[i])
		    return (-1);
        i++;
    }
    t[i]=NULL;
    closedir(dir);
    return 0;
}

int	ft_get_wc_list(char *str, t_extra *x, char **t)
{
	int i = 0;
    int s;
	char cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		return (-1);
	s = ft_get_wc_list_size(cwd);
	if (s == -1)
		return (-1);
	t = malloc((s + 1) * sizeof(char *));
	if (!t)
		return (-1);
    if(ft_get_wc_list_filled(t, s, cwd)==-1)
            return (ft_free(t), -1);
    return 0;
}
