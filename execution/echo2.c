/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 07:32:22 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/08 05:38:32 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

//    add later to libft
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

//--------------------------- new func :

int	ft_check_ptr_value(char c, int f) // add checks in one function withe flags to chose
{
	if (f == 0)
	{
		if (c && (c == '?' || c == '@' || c == '_' || ft_isalnum(c))) 
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

int	ft_calcul_var_len(char *ptr) // clacul the len of malloc
{
	int	s;

	s = 0;
	if (ft_check_ptr_value(*ptr, 1)) 
	{
		return (1);
	}
	else
	{
		while (ft_check_ptr_value(*ptr, 2))
		{
			s++;
			ptr++;
		}
	}
	return (s);
}

void	ft_print_expanded_variable(t_env *env_list, char *var_name) // match the env and print 
{
	t_env	*env;

	env = env_list;
	while (env)
	{
		if (ft_strcmp(var_name, env->name) == 0)
		{
			ft_putstr(env->value);
			break ;
		}
		env = env->next;
	}
}

int	ft_toggle_quote(char **ptr, int *in_single_quote, int *in_double_quote)
{
	if (**ptr == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		(*ptr)++;
		return (1);
	}
	if (**ptr == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		(*ptr)++;
		return (1);
	}
	return (0);
}

char	*ft_copy_expand_var(char **ptr, int *f) // the copy part
{
	char	*var_name;
	int		j;

	j = 0;
	var_name = malloc(ft_calcul_var_len(*ptr) + 1);
	if (!var_name)
		return (NULL); // return NULL to signal allocation failure
	if (ft_check_ptr_value(**ptr, 1))
	{
		var_name[j++] = *(*ptr)++;
		*f == 1;
	}
	else
	{
		while (ft_check_ptr_value(**ptr, 2))
			var_name[j++] = *(*ptr)++;
	}
	var_name[j] = '\0';
	return (var_name);
}

void	ft_handle_special_char(char *var_name)
{
	// if (ft_strcmp(var_name, "?") == 0)
	// {
	// 	// extern int g_exit_status;
	// 	// ft_putnbr(g_exit_status);
	// }
	return ;
}

//--------------------------- end .

int	ft_is_n_flag(char *str)
{
	if (!str || str[0] != '-')
		return (0);
	str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

void	ft_print_expanded_arg(char *ptr, t_env *env_list)
{
	char *var_name; // fix static , a.k.a segfault ....
	int(in_single_quote), (in_double_quote), f = 0;  //f is flage for the print part if we found '?' '@' ....
	
	in_single_quote = 0;
	in_double_quote = 0;
	if (!ptr)
		return ;
	while (*ptr)
	{
		if (ft_toggle_quote(&ptr, &in_single_quote, &in_double_quote)) // toogle in one function
			continue ;
		if (*ptr == '$' && ft_check_ptr_value(*(ptr + 1), 0) && !in_single_quote)  // ft_check..() handle the mathcing with 0 1 2 flgs 
		{
			
			var_name = (ptr++, ft_copy_expand_var(&ptr, &f)); // creat the var_name and copy the content
			if (!var_name)
				return ; // we may need to return -1 or not ...
				
			if (f == 1) // if the table ony have 1 cahr aka '?' ... 
				ft_handle_special_char(var_name);
			else  // print the var
				ft_print_expanded_variable(env_list, var_name);
			free(var_name);
		}
		else
			(ft_putchar(*ptr), ptr++);
	}
}

int	ft_echo(t_token *data)
{
	int	newline;
	int	i;
	int	first_arg;

	newline = 1;
	i = 1;
	first_arg = 1;
	if (!data || !data->c_arg || !data->c_arg[0])
		return (ft_putstr("\n"), 0);
	while (data->c_arg[i] && ft_is_n_flag(data->c_arg[i]))
	{
		newline = 0;
		i++;
	}
	while (data->c_arg[i])
	{
		if (!first_arg)
			ft_putstr(" ");
		ft_print_expanded_arg(data->c_arg[i], data->env_list);
		first_arg = 0;
		i++;
	}
	if (newline)
		ft_putstr("\n");
	return (0);
}
