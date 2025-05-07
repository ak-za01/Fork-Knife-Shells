/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:46:46 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/02 15:57:49 by anktiri          ###   ########.fr       */
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
// typedef struct s_env
// {
//     char *name;
//     char *value;
//     struct s_env *next;
// } t_env;

// Return values
# define SUCCESS 0
# define ERROR 1

// Built-in function prototypes
int ft_echo(t_token	*data);
// int ft_cd(t_token	*data, t_env *env_list);
int ft_pwd(void);
int ft_export(t_token	*data);
// int ft_unset(t_token	*data, t_env **env_list);
int ft_env(t_token	*data);
int ft_exit(t_token	*data);

// //	Helper functions
int		exec_builtin(t_token *data);
t_env	*create_env_list(char **env);
void	free_env_list(t_env **env_list);
char	**ft_split_env(char const *s, char c);
// char *get_env_value(t_env *env_list, char *name);

#endif