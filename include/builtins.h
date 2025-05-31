/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:46:46 by anktiri           #+#    #+#             */
/*   Updated: 2025/05/31 18:33:36 by anktiri          ###   ########.fr       */
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

//	execution functions
int		exec_cmd(t_token *data, t_extra x);
int		exec_single(t_token *data, t_extra x);


// Built-in function prototypes
int		ft_echo(t_token	*data);
int		ft_cd(char **c_args, t_extra x);
int		ft_pwd(void);
int		ft_export(t_token *data, t_extra x);
int		ft_unset(t_token *data, t_extra x);
int		ft_env(t_token	*data, t_extra x);
int		ft_exit(t_token	*data, t_extra x);

//	Helper functions
int		exec_builtin(t_token *data, t_extra x);
t_env	*create_env_list(char **env);
void	free_env_list(t_extra *x);
char	**ft_split_env(char const *s, char c);
void	error_message(char *cmd, char *str);
int		update_pwd(t_extra x, char *old_dir);
char	*get_env_value(t_env *env_list, char *name);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	init_extra(t_extra *x, char **env);
int		var_exist(t_env *env_list, char *name);
int		add_var(t_env *env_list, char *name, char *value);


//	Helper functions for export
int		search_variable(t_env **current, char *str);
t_env	*add_new_node(char *arg, t_env *env_list);
int		valid_variable(char *str);
void	sort_env_list(t_env *env_list, t_env **copy);
void	print_env_node(t_env *node);
void	free_temp_env(t_env *node);
void	print_env_list(t_env *list);


// char *get_env_value(t_env *env_list, char *name);

#endif