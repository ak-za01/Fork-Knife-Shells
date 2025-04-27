/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 07:32:22 by anktiri           #+#    #+#             */
/*   Updated: 2025/04/27 08:44:53 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int is_n_flag(char *str)
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

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void print_expanded_arg(char *arg, t_env *env_list)
{
    char *ptr = arg;
    char *end = arg + ft_strlen(arg);
    char var_name[256];
    int j;
    int is_single_quoted;
    int is_double_quoted;

	is_single_quoted = (arg[0] == '\'' && end > arg && *(end - 1) == '\'');
    is_double_quoted = (arg[0] == '"' && end > arg && *(end - 1) == '"');
    if (is_single_quoted || is_double_quoted)
    {
        ptr++;
        end--;
    }

    if (is_single_quoted)
    {
        while (ptr < end)
        {
            ft_putchar(*ptr);
            ptr++;
        }
        return;
    }
    while (ptr < end)
    {
        if (*ptr == '$' && *(ptr + 1) && (ft_isalnum(*(ptr + 1)) || *(ptr + 1) == '?'))
        {
            ptr++;
            j = 0;
            while (ptr < end && (ft_isalnum(*ptr) || *ptr == '_'))
                var_name[j++] = *ptr++;
            if (j == 0 && *(ptr - 1) == '?')
            {
                var_name[j++] = '?';
            }
            var_name[j] = '\0';

            if (ft_strcmp(var_name, "?") == 0)
            {
                // extern int g_exit_status;
                // printf("%d", g_exit_status);
            }
            else
            {
                t_env *env = env_list;
                while (env)
                {
                    if (ft_strcmp(var_name, env->name) == 0)
                    {
                        printf("%s", env->value);
                        break;
                    }
                    env = env->next;
                }
            }
        }
        else
        {
            putchar(*ptr);
            ptr++;
        }
    }
}

int ft_echo(t_token *data)
{
    int newline = 1;
    int i = 1;
    int first_arg = 1;

    if (!data || !data->c_arg || !data->c_arg[0])
    {
        printf("\n");
        return (SUCCESS);
    }
    while (data->c_arg[i] && is_n_flag(data->c_arg[i]))
    {
        newline = 0;
        i++;
    }
    while (data->c_arg[i])
    {
        if (!first_arg && !((data->c_arg[i-1][0] == '\'' ||
				data->c_arg[i-1][0] == '"') || (data->c_arg[i][0] == '\''
				|| data->c_arg[i][0] == '"')))
            printf(" ");
        print_expanded_arg(data->c_arg[i], data->env_list);
        first_arg = 0;
        i++;
    }
    if (newline)
        printf("\n");
    return (SUCCESS);
}
