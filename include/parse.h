/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:45:32 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/11 17:06:19 by anktiri          ###   ########.fr       */
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
	struct				s_env *next;
}						t_env;

typedef struct s_extra
{
	t_env *env_list;
	int exit_status;
	
}				t_extra;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	t_token_precedence	prec;
	t_env				*env_list;
	char				**c_arg;
	char				**c_red;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

//------------------------------ Parsing :
t_token					*ft_parse(char *str);

//------------------------------Ttokenizing :
int						ft_tokenize(char *str, t_token **data);
int						ft_initialize_list(char *str, t_token **data);
void					ft_set_tokens(t_token **data);
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

//------------------------------ Shunting Yard :
void					ft_shunting_yard(t_token **data);
void					set_precedence(t_token **data);
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
char					**ft_set_charset(void);

#endif