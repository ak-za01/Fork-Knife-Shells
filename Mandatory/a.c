/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:29:56 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/08 17:22:13 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	ft_free(char **t);


void	ft_fix_norminet_1(char *a, char const *b, long *n1)
{
	*a = *b;
	(*n1) = !(*n1);
}

void	ft_fix_norminet_2(long *n2, long *n1)
{
	(*n1)++;
	(*n2)++;
}

long	ft_count_split2(char const *s, char c)
{
	long	i;
	long	f;
	long	i_c;
	char	q;
	long	count;

	i = 0;
	f = 0;
	i_c = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && i_c == 0)
			ft_fix_norminet_1(&q, s + i, &i_c);
		else if (i_c == 1 && s[i] == q)
			i_c = !i_c;
		if (s[i] != c && f == 0 && i_c == 0)
			ft_fix_norminet_2(&f, &count);
		else if (s[i] == c)
			f = 0;
		i++;
	}
	if (i_c == 1)
		return (-1);
	return (count);
}

char	*ft_copy_split2(const char *s, char c, long *i)
{
	long	j;
	long	k;
	long	i_c;
	char	q;
	char	*t;

	i_c = 0;
	k = 0;
	j = *i;
	while (s[j] && (s[j] != c || i_c == 1))
	{
		if ((s[j] == '\'' || s[j] == '\"') && i_c == 0)
			ft_fix_norminet_1(&q, s + j, &i_c);
		else if (i_c == 1 && s[j] == q)
			i_c = !i_c;
		j++;
	}
	t = malloc((j - *i + 1) * 1);
	if (!t)
		return (NULL);
	while (*i < j)
		t[k++] = s[(*i)++];
	t[k] = '\0';
	return (t);
}


char	**ft_split2(char const *s, char c)
{
	long	i;
	long	k;
	char	**t;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	if ((ft_count_split2(s, c)) == -1)
		return (NULL);
	t = malloc((ft_count_split2(s, c) + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	while (k < ft_count_split2(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		t[k] = ft_copy_split2(s, c, &i);
		if (!t[k])
			return (ft_free(t), NULL);
		k++;
	}
	t[k] = NULL;
	return (t);
}

void	ft_free(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}
void	ft_print_tab(char **t)
{
	int	i;

	i = 0;
	if (!t)
		return ;
	while (t[i])
	{
		printf("\n\t\t > %s <\n", t[i]);
		i++;
	}
}

int	main(void)
{
	char	**t;
	int c=ft_count_split2(" \"a   \"                 \'asdf fsdf\'           ", ' ');
	// char **t = ft_split4("a bc\'\'   \'a\'  \"ab\'c\"abc");
	// t = ft_split2;
	// ft_print_tab(t);
	printf("%d\n", c);
	return (0);
}
