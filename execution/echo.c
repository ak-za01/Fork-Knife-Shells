/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 07:32:22 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/12 12:51:00 by noctis           ###   ########.fr       */
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

void print_expanded_arg(char *arg, t_env *env_list)
{
    char *ptr = arg;
    char var_name[256];
    int j;
    int in_single_quote = 0;
    int in_double_quote = 0;

    if (!arg)
        return;

    while (*ptr)
    {
        // Toggle quote states
        if (*ptr == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            ptr++;
            continue;
        }
        if (*ptr == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            ptr++;
            continue;
        }

        // Handle variable expansion outside single quotes
        if (*ptr == '$' && *(ptr + 1) && (ft_isalnum(*(ptr + 1)) || *(ptr + 1) == '?') && !in_single_quote)
        {
            ptr++;
            j = 0;
            if (*ptr == '?')
            {
                var_name[j++] = *ptr++;
            }
            else
            {
                while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
                    var_name[j++] = *ptr++;
            }
            var_name[j] = '\0';

            if (ft_strcmp(var_name, "?") == 0)
            {
                // extern int g_exit_status;
                // ft_putnbr(g_exit_status);
            }
            else
            {
                t_env *env = env_list;
                while (env)
                {
                    if (ft_strcmp(var_name, env->name) == 0)
                    {
                        ft_putstr(env->value);
                        break;
                    }
                    env = env->next;
                }
            }
        }
        else
        {
            ft_putchar(*ptr);
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
        ft_putstr("\n");
        return (0);
    }

    // Check for -n flags
    while (data->c_arg[i] && is_n_flag(data->c_arg[i]))
    {
        newline = 0;
        i++;
    }

    // Process each argument
    while (data->c_arg[i])
    {
        if (!first_arg)
            ft_putstr(" ");
        print_expanded_arg(data->c_arg[i], data->env_list);
        first_arg = 0;
        i++;
    }

    // Print newline if -n is not specified
    if (newline)
        ft_putstr("\n");

    return (0);
}
