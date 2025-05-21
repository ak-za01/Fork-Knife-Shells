/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:46:46 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/21 12:09:11 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include "main.h"

// Return values
# define SUCCESS 0
# define ERROR 1

// Built-in function prototypes
int ft_echo(t_token	*data);
int ft_cd(char **c_args, t_extra x);
int ft_pwd(void);
int ft_export(t_token *data, t_extra x);
int ft_unset(t_token *data, t_extra x);
int ft_env(t_token	*data, t_extra x);
int ft_exit(t_token	*data, t_extra x);

// //	Helper functions
int		exec_builtin(t_token *data, t_extra x);
t_env	*create_env_list(char **env);
void	free_env_list(t_extra *x);
char	**ft_split_env(char const *s, char c);

// //	Helper functions for export
int		search_variable(t_env **current, char *str);
t_env	*add_new_node(char *arg, t_env *env_list);
int		valid_variable(char *str);
void	sort_env_list(t_env *env_list, t_env **original, t_env **added);
void	print_export(t_env *env_list);
void	print_env_node(t_env *node);
void	free_temp_env(t_env *node);

int	update_pwd(t_extra x, char *old_dir);

// char *get_env_value(t_env *env_list, char *name);

#endif