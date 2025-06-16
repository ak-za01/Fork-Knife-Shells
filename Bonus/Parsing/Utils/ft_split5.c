/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:48:10 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/13 19:49:49 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

char	**ft_split5(char const *str)
{
	int		i;
	int		x;
	int		s;
	char	**t;
	char	**charset;

	charset = ft_set_charset2();
	if (!charset)
		return (NULL);
	i = 0;
	x = 0;
	s = ft_count_split5(str, charset);
	t = malloc(sizeof(char *) * (s + 1));
	if (!t)
		return (NULL);
	while (i < s)
	{
		t[i] = ft_copy_split5(str, charset, &x);
		if (!t[i])
			return (free(charset), ft_free(t), NULL);
		i++;
	}
	t[i] = NULL;
	return (free(charset), t);
}

int	ft_count_split5(const char *str, char **charset)
{
	int		i;
	int		count;
	int		skip;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (str[i])
	{
		skip = 0;
		if (!quote && ft_is_special2(&str[i], charset, &skip) && str[i] != '\''
			&& str[i] != '\"')
		{
			count++;
			i += skip;
			continue ;
		}
		count += ft_skip_token_quoted2(str, charset, &i);
	}
	return (count);
}

char	*ft_copy_split5(const char *str, char **charset, int *x)
{
	int		j;
	int		s;
	int		start;
	int		skip;
	char	*t;

	start = *x;
	skip = 0;
	if (ft_is_special2(&str[*x], charset, &skip) && str[*x] != '\''
		&& str[*x] != '\"')
		*x += skip;
	else
		ft_skip_token_quoted2(str, charset, x);
	s = *x - start;
	t = malloc(s + 1);
	if (!t)
		return (NULL);
	j = 0;
	while (j < s)
	{
		t[j] = str[start + j];
		j++;
	}
	t[s] = '\0';
	return (t);
}

int	ft_is_special2(const char *str, char **charset, int *len)
{
	int	i;
	int	s;

	i = 0;
	while (charset[i])
	{
		s = ft_strlen(charset[i]);
		if (ft_strncmp(str, charset[i], s) == 0)
		{
			*len = s;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_skip_token_quoted2(const char *str, char **charset, int *i)
{
	int		skip;
	char	quote;

	skip = 0;
	quote = 0;
	while (str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			if (!quote)
				quote = str[*i];
			else if (quote == str[*i])
				quote = 0;
			(*i)++;
			continue ;
		}
		if (!quote && ft_is_special(&str[*i], charset, &skip) && str[*i] != '\''
			&& str[*i] != '\"')
			break ;
		(*i)++;
	}
	return (1);
}
