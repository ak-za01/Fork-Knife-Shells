/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:45:32 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/16 16:57:19 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum e_token_type
{
	pipe_t,
	heredoc_t,
	append_t,
	outfile_t,
	infile_t,
	string_t,
	cmd_t,
	b_cmd_t,
	cmd_arg_t,
	ambiguous_t,
	skip_t,
	free_t,
	undefiend,
	end_t
}					t_token_type;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				original;
	struct s_env	*next;
}					t_env;

typedef struct s_extra
{
	t_env			*env_list;
	int				exit_status;
	char			*cmd_path;
	char			**env;
	int				stdin_backup;
	int				stdout_backup;
	int				pipe_count;
	int				cmd_index;
	int				**pipefd;
	int				prev_pipe_read;
}					t_extra;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				f;
	int				arg_s;
	char			**c_arg;
	int				red_s;
	char			**c_red;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_norm
{
	char			*var;
	char			*t;
}					t_norm;

typedef struct s_wc
{
	char			*value;
	int				f;
	struct s_wc		*next;
	struct s_wc		*prev;
}					t_wc;

//------------------------------ Parsing :
t_token				*ft_parse(char *str, t_extra *x);

//------------------------------Ttokenizing :
int					ft_tokenize(char *str, t_token **data, t_extra *x);
int					ft_initialize_list(char *str, t_token **data);
int					ft_check_string(char *str);
void				ft_set_tokens_befor_expanding(t_token **data);
void				ft_fix_cmd_pos_token(t_token **data);
t_token_type		ft_get_token_type(char *t, int f);
int					ft_check_buildin_cmd(char *t);
int					ft_check_word(char *t1, char *t2);
int					ft_validat_list(t_token **data, t_extra *x);
int					ft_validat_list_2(t_token *ptr, t_extra *x);
void				ft_put_error_tokens(int f, int fd, t_extra *x);
t_token				*ft_creat_new_list(char *str, t_token_type type);
void				ft_add_list_front(t_token **data, t_token *n);
void				ft_add_list_end(t_token **data, t_token *n);
t_token				*ft_last_list(t_token *data);
void				ft_free_list(t_token **data);

//------------------------------ Expanding :
int					ft_expand(t_token **data, t_extra *x);
int					ft_expanding_list(t_token **data, t_extra *x);
int					ft_re_tokenizing(t_token **data);
int					ft_fix_list(t_token **data);
void				ft_free_arg_node3(t_token **data);
int					ft_handle_cas_1(t_token **data, t_token *ptr);
int					ft_check_if_ambiguous(char *str);
int					ft_add_nodes(char *t, t_token *ptr, t_token **data);
void				ft_connect_list(t_token *prev, t_token *next, t_token *new,
						t_token **data);
void				ft_set_mini_tokens(t_token **new);
int					ft_handle_cas_2(t_token *ptr);
int					ft_get_node_count(t_token *ptr);
int					ft_remove_quotes(t_token **data);
char				*ft_remove_q(char *str);
void				ft_copy_withe_no_q(char *rs, char **t, int i, int k);
int					ft_count_size(char **t);
void				ft_set_tokens_after_expanding(t_token **data);
void				ft_fix_cmd_pos_token2(t_token **data);
t_token_type		ft_get_token_type2(char *t, int f, int exp);
int					ft_toggle_quote(char **ptr, int *s_q, int *d_q);
int					ft_calcul_total_len(int s, char *ptr, t_extra *x, int f);
int					ft_calculs_exp_len(t_env *env_list, char *var);
int					ft_calcul_var_len(char *ptr);
int					ft_calcul_sepcial_len(char *var, t_extra *x);
int					ft_swap_value_fix_norm(int f, t_extra *x, t_norm *n_data,
						int *i);
int					ft_calcul_total_len_fix_norm(t_extra *x, int f, int *s,
						char **ptr);
char				*ft_swap_value(int i, char *ptr, t_extra *x, int f);
int					ft_check_ptr_value(char c, int f);
char				*ft_get_expand_name(char **ptr, int *f);
void				ft_copy_exp_value(t_env *env_list, char *var, char *t,
						int *i);
int					ft_handle_special_char(t_extra *x, char *var, char *t,
						int *i);
int					ft_check_dollar(char *t);
int					ft_check_q_status(char *t);
int					ft_strlen_2(char **t);
int					ft_strcmp(const char *s1, const char *s2);

//------------------------------ Wildcards :
int					ft_wildcard(t_token **data);
int					ft_check_wc_string(char *t);

char				**ft_get_wc_list(char *str);
void				ft_sort_wc_list_final(char **t);

int					ft_cmd_list(char *str, t_wc **data);
void				ft_add_list_end2(t_wc **data, t_wc *n);
char				*ft_prosses_wc_string(char *t1);
t_wc				*ft_creat_new_list2(char *str, int i);
void				ft_free_list2(t_wc **data);

char				**ft_files_list(const char *cwd, t_wc *data);
int					ft_get_wc_list_filled(char **t, const char *cwd, int f);
int					ft_copy_wc_string(char **t, int *i, char *str);
int					ft_get_wc_list_size(const char *cwd, int f);
int					ft_is_hidden(t_wc *data);

char				**ft_filter_wc_list(char **t1, t_wc *data, int i, int j);
int					ft_count_wc_match(char **t1, t_wc *data);
int					ft_valide(char *t, t_wc *data);
int					ft_consume(char *t, int *i, t_wc *ptr, size_t s1);

int					ft_fix_wc_list(t_token **data, t_token **ptr, char **t);
int					ft_add_nodes2(t_token **data, t_token **ptr, char **t);
void				ft_set_mini_tokens2(t_token **new);

//------------------------------ Filter 1  :
int					ft_filter_list(t_token **data);
int					ft_remove_end_token(t_token **data);
long				ft_count_arg_node(t_token *ptr, int f);
int					ft_copy_arg_node(t_token *ptr);
void				ft_free_arg_node(t_token **data);

//------------------------------ Filter 2 :
int					ft_filter_list2(t_token **data);
int					ft_filter_search(t_token *ptr);
int					ft_filter_cas_1(t_token **ptr);
int					ft_filter_cas_2(t_token **ptr);
void				ft_free_arg_node2(t_token **data);

//------------------------------ Utils :
char				**ft_split2(char const *s, char c);
long				ft_count_split2(char const *s, char c);
char				*ft_copy_split2(const char *s, char c, long *i);
void				ft_fix_norminet_1(char *a, char const *b, long *n1);
void				ft_fix_norminet_2(long *n2, long *n1);

char				**ft_split3(char const *s);
int					ft_count_split3(const char *str, char **charset);
char				*ft_copy_split3(const char *str, char **charset, int *x);
int					ft_skip_token_quoted(const char *str, char **charset,
						int *i);
int					ft_is_special(const char *str, char **charset, int *len);

char				**ft_split4(char const *str);
int					ft_count_split4(char const *s);
char				*ft_copy_split4(char const *s, int *k);

char				**ft_split5(char const *str);
int					ft_count_split5(const char *str, char **charset);
char				*ft_copy_split5(const char *str, char **charset, int *x);
int					ft_is_special2(const char *str, char **charset, int *len);
int					ft_skip_token_quoted2(const char *str, char **charset,
						int *i);

char				*ft_strjoin4(char **s1);

void				ft_free(char **t);
void				ft_free2(char **t, int s);
char				**ft_set_charset(void);
char				**ft_set_charset2(void);

#endif