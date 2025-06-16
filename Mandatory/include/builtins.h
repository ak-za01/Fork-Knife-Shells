/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:46:46 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/16 18:29:13 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

// Return values
# define SUCCESS 0
# define ERROR 1

int		pipes_count(t_token *data);
int		ft_dup2(int f1, int f2);
int		exec_external(t_token *data, t_extra *x);
int		cleanup_execution_vars(t_extra *x);
int		create_pipe(t_extra *x);
int		setup_pipe(int index, int cmd_count, int **pipefd);
int		cmd_error(char *cmd, int status);
int		free_pipes(t_extra *x, int i);
void	close_pipe_in_parent(t_extra *x);
void	close_all_pipes(t_extra *x);
void	exec_child(t_token *data, t_extra *x);
int		handle_ambiguous(int a, int red_s);

//	execution functions
int		exec_cmd(t_token *data, t_extra *x);
int		exec_single(t_token *data, t_extra *x);

// Redirection Functions
int		setup_redirections(t_token *data, t_extra *x);
int		setup_heredoc(t_token *data, t_extra *x);
int		process_heredoc(t_token *data, t_extra *x);
int		handle_heredoc(char *del);
int		has_heredoc(char **c_red);
int		restore_std_fds(t_extra *x);
void	print_error(char *file, char *error_msg);

// Built-in function prototypes
int		ft_echo(t_token *data);
int		ft_cd(char **c_args, t_extra x);
int		ft_pwd(void);
int		ft_export(t_token *data, t_extra x);
int		ft_unset(t_token *data, t_extra x);
int		ft_env(t_token *data, t_extra x);
int		ft_exit(t_token *data, t_extra x);

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

#endif