/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 04:56:46 by anktiri           #+#    #+#             */
/*   Updated: 2025/04/22 06:02:46 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include "main.h"

// Struct for environment variables
typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
} t_env;

// Return values
# define SUCCESS 0
# define ERROR 1

// Built-in function prototypes
int ft_echo(char **args);
// int ft_cd(char **args, t_env *env_list);
int ft_pwd(void);
// int ft_export(char **args, t_env **env_list);
// int ft_unset(char **args, t_env **env_list);
int ft_env(t_env *env_list);
int ft_exit(char **args);

// //	Helper functions
int is_builtin(char *cmd);
int exec_builtin(char **args, t_env **env_list);
t_env *create_env_list(char **env);
// void free_env_list(t_env *env_list);
// char *get_env_value(t_env *env_list, char *name);

#endif