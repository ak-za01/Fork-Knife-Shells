/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:45:32 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/31 19:53:11 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum e_token_type
{
	pipe_t,
	append_t,
	heredoc_t,
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
}						t_token_type;

typedef enum e_token_precedence
{
	string_p,
	pipe_p,
}						t_token_precedence;

typedef struct s_env
{
	char				*name;
	char				*value;
	int					original;
	struct s_env		*next;
}						t_env;

typedef struct s_extra
{
	t_env				*env_list;
	int					exit_status;
	char				*cmd_path;
	char				**env;
	int					stdin_backup;
    int					stdout_backup;
    int					pipe_count;
    int					cmd_index;
    int					**pipefd;
    int					prev_pipe_read;
}						t_extra;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	t_token_precedence	prec;
	int					f;
	int					arg_s;
	char				**c_arg;
	int					red_s;
	char				**c_red;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

//------------------------------ Parsing :
t_token					*ft_parse(char *str, t_extra *x);

//------------------------------Ttokenizing :
int						ft_tokenize(char *str, t_token **data);
int						ft_initialize_list(char *str, t_token **data);
void					ft_set_tokens_befor_expanding(t_token **data);
void					ft_fix_cmd_pos_token(t_token **data);
t_token_type			ft_get_token_type(char *t, int f);
int						ft_check_buildin_cmd(char *t);
int						ft_check_word(char *t1, char *t2);
int						ft_validat_list(t_token **data);
int						ft_validat_list_2(t_token *ptr);
void					ft_put_error_tokens(int f, int fd);
t_token					*ft_creat_new_list(char *str, t_token_type type);
void					ft_add_list_front(t_token **data, t_token *n);
void					ft_add_list_end(t_token **data, t_token *n);
t_token					*ft_last_list(t_token *data);
void					ft_free_list(t_token **data);

//------------------------------ Expanding :
int						ft_expand(t_token **data, t_extra *x);
int						ft_expanding_list(t_token **data, t_extra *x);
char					*ft_swap_value(int i, char *ptr, t_extra *x);
int						ft_check_ptr_value(char c, int f);
char					*ft_get_expand_name(char **ptr, int *f);
void					ft_copy_exp_value(t_env *env_list, char *var, char *t,
							int *i);
void					ft_handle_special_char(t_extra *x, char *var,
							char *t, int *i);
int						ft_toggle_quote(char **ptr, int *s_q, int *d_q);
int						ft_calculs_exp_len(t_env *env_list, char *var);
int						ft_calcul_total_len(int s, char *ptr, t_extra *x);
int						ft_calcul_var_len(char *ptr);
int						ft_calcul_sepcial_len(char *var, t_env *env_list);
int						ft_fix_list(t_token **data);
int						ft_handle_cas_1(t_token **data, t_token *ptr);
int						ft_add_nodes(char *t, t_token *ptr, t_token **data);
void					ft_connect_list(t_token *prev, t_token *next,
							t_token *new, t_token **data);
void					ft_set_mini_tokens(t_token **new);
int						ft_handle_cas_2(t_token *ptr);
int						ft_get_node_count(t_token *ptr);
void					ft_free_arg_node3(t_token **data);
void					ft_fix_cmd_pos_token2(t_token **data);
t_token_type			ft_get_token_type2(char *t, int f, int exp);
void					ft_set_tokens_after_expanding(t_token **data);
int						ft_check(char *t);
int						ft_strlen_2(char **t);
int						ft_strcmp(const char *s1, const char *s2);

//------------------------------ Shunting Yard :
void					ft_shunting_yard(t_token **data);
void					ft_set_precedence(t_token **data);
void					ft_move_list_shunting_yard(t_token **data, t_token **a,
							t_token **b);
void					ft_push(t_token **data, t_token **a);
void					ft_pop(t_token **b, t_token **a);

//------------------------------ Filter 1  :
int						ft_filter_list(t_token **data);
int						ft_remove_end_token(t_token **data);
long					ft_count_arg_node(t_token *ptr, int f);
int						ft_copy_arg_node(t_token *ptr);
void					ft_free_arg_node(t_token **data);

//------------------------------ Filter 2 :
int						ft_filter_list2(t_token **data);
int						ft_filter_search(t_token *ptr);
int						ft_filter_cas_1(t_token **ptr);
int						ft_filter_cas_2(t_token **ptr);
void					ft_free_arg_node2(t_token **data);

//------------------------------ Utils :
char					**ft_split2(char const *s, char c);
long					ft_count_split2(char const *s, char c);
char					*ft_copy_split2(const char *s, char c, long *i);
void					ft_fix_norminet_1(char *a, char const *b, long *n1);
void					ft_fix_norminet_2(long *n2, long *n1);

char					**ft_split3(char const *s);
int						ft_count_split3(const char *str, char **charset);
char					*ft_copy_split3(const char *str, char **charset,
							int *x);
int						ft_skip_token_quoted(const char *str, char **charset,
							int *i);
int						ft_is_special(const char *str, char **charset,
							int *len);

void					ft_free(char **t);
void					ft_free2(char **t, int s);
char					**ft_set_charset(void);

#endif