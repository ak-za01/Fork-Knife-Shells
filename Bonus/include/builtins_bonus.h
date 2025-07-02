/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:46:46 by anktiri           #+#    #+#             */
/*   Updated: 2025/07/02 16:33:13 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_BONUS_H
# define BUILTINS_BONUS_H

# include "main_bonus.h"

// Return values
# define SUCCESS 0
# define ERROR 1

int		pipes_count(t_token *data);
int		ft_dup2(int f1, int f2);
int		exec_external(t_token *data, t_extra *x);
int		cleanup_execution_vars(t_token *data, t_extra *x);
int		create_pipe(t_extra *x);
int		setup_pipe(int index, int cmd_count, int **pipefd);
int		cmd_error(char *cmd, int f);
void	close_pipe_in_parent(t_extra *x);
void	close_all_pipes(t_extra *x);
void	exec_child(t_token *data, t_extra *x);
int		handle_ambiguous(int a, int red_s);
int		free_pipes(t_extra *x, int i);
void	free_pipe(t_extra *x);
int		file_errors(char *file, int output);
int		file_errors2(char *file);
void	failled_pipes(t_extra *x);
int		external_helper(t_token *current, t_extra *x);
char	*find_path(char *cmd, t_env *env_list, int i);
char	**env_to_arr(t_env *env_list);

//	execution functions
int		ft_execution(t_token *data, t_extra *x);
int		exec_single(t_token *data, t_extra *x);
void	free_external(char *cmd_path, char **env);
int		cmd_error1(char *cmd);

// Redirection Functions
int		setup_redirections(t_token *data, t_extra *x);
int		restore_std_fds(t_extra *x);
void	print_error(char *file, char *error_msg);
int		handle_hd(t_token *data);

// heredoc Functions
int		has_heredoc(char **c_red);
int		count_heredoc(t_token *data);
int		ft_check33(char *t, char *ar);
int		ft_check_q_status2(char *t);
int		filter_heredoc_line(char **line, char *del, t_extra *x);
int		check_signal(t_token *data, char *line, int f);
int		handle_heredoc1(char *del, t_token *data, t_extra *x);
int		handle_heredoc2(char *del, t_token *data, t_extra *x);
int		process_heredoc(t_token *data, t_extra *x, int a, int c2);
int		handle_single_heredoc(t_token *current, t_extra *x);
int		setup_heredoc(t_token *data, t_extra *x);

// Built-in function prototypes
int		ft_echo(t_token *data);
int		ft_cd(char **c_args, t_extra *x);
int		ft_pwd(t_env *env_list);
int		ft_export(t_token *data, t_extra *x);
int		ft_unset(t_token *data, t_extra **x);
int		ft_env(t_token *data, t_extra *x);
int		ft_exit(t_token *data, t_extra *x);

//	Helper functions
int		exec_builtin(t_token *data, t_extra *x);
t_env	*create_env_list(char **env);
void	free_env_list(t_extra *x);
char	**ft_split_env(char const *s, char c);
void	error_message(char *cmd, char *str);
int		update_pwd(t_extra *x, char *old_dir);
char	*get_env_value(t_env *env_list, char *name);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	init_extra(t_extra *x, char **env);
int		var_exist(t_env *env_list, char *name);
int		add_var(t_env *env_list, char *name, char *value);
t_env	*create_env_node(char *env_str);
int		get_var(t_env *env_list, char *name, char *value);
int		expand_tilde(char *home, char *path, char *old_dir, t_extra *x);
void	chdir_error(char *path);
void	shellvl_error(int new_value);

//	Helper functions for export
int		search_variable(t_env **current, char *str);
t_env	*add_new_node(char *arg, t_env *env_list);
int		valid_variable(char *str);
void	sort_env_list(t_env *env_list, t_env **copy);
void	print_env_node(t_env *node);
void	free_temp_env(t_env *node);
void	print_env_list(t_env *list);

//	signal functions
void	signal_init_interactive(void);
void	signal_init_exec(void);
void	signal_init_heredoc(void);
void	signal_init_child(void);
void	handle_signal_in_main(t_extra *x);
void	sig_handler_interactive(int signal);
void	sig_handler_heredoc(int signal);

#endif