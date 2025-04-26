/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:45:32 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/26 21:16:31 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum e_token_type
{
	pipe_t,    // 0 : |
	append_t,  // 1 : >>
	heredoc_t, // 2 : <<
	outfile_t, // 3 : >
	infile_t,  // 4 : <
	string_t,  // 5
	cmd_t,     // 6
	b_cmd_t,   // 7
	cmd_arg_t, // 8
	end_t      // 9
}						t_token_type;

typedef enum e_token_precedence
{
	end_p,     // 0
	string_p,  // 1
	pipe_p,    // 2
	redirect_p // 3
}						t_token_precedence;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	t_token_precedence	prec;
	char				**c_arg;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

// parsing :
t_token					*ft_parse(char *str);

// tokenizing
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

// Shunting yard
void					ft_shunting_yard(t_token **data);
void					set_precedence(t_token **data);
void					ft_move_list_shunting_yard(t_token **data, t_token **a,
							t_token **b);
void					ft_push(t_token **data, t_token **a);
void					ft_pop(t_token **b, t_token **a);

// filter
int						ft_filter_list(t_token **data);
void					ft_remove_end_token(t_token **data);
long					ft_count_arg_node(t_token *ptr);
int						ft_copy_arg_node(t_token *ptr);
void					ft_free_arg_node(t_token **data);

// utils
char					**ft_split2(char const *s, char c);
char					**ft_split3(char const *s);
void					ft_free(char **t);
char					**ft_set_charset(void);

#endif