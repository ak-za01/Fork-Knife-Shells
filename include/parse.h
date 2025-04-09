/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:45:32 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/08 19:04:52 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

typedef enum e_token_type
{
    pipe_t,          // 0
    infile_t,        // 1
    heredoc_t,       // 2
    outfile_t,       // 3
    append_t,        // 4
    string_t,        // 5
    cmd_t,           // 6
    b_cmd_t,         // 7
    cmd_arg_t,       // 8
    end_t             // 9
}   t_token_type;

typedef struct s_token 
{
   char *value;
   t_token_type type;
//    int index;
   struct s_token *next;
   struct s_token *prev; 
}   t_token;


                        // parsing :
void ft_parse(char *str);

                        // tokenizing
int ft_tokenize(char *str, t_token **data);
int	ft_initialize_list(char *str, t_token **data);


t_token *ft_creat_new_list(char *str, t_token_type type);
void ft_add_list_front(t_token **data, t_token *n);
void ft_add_list_end(t_token **data, t_token *n);
void ft_free_list(t_token **data);

                        //utils
char	**ft_split2(char const *s, char c);
// char	**ft_split3(char const *s);
char	**ft_split3(char const *s);
void ft_free(char **t);

#endif