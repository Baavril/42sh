/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <tgouedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:53 by tgouedar          #+#    #+#             */
/*   Updated: 2020/05/12 13:59:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "tokens.h"

int					ft_trim_comment(void);
int					ft_istoken(char *str);
int					ft_is_quote(char c);
char				**lexer_verbose(char **input);
struct s_token		get_next_token(char *str);
t_token				get_next_token_alias(char *str);
void				ft_free_token(t_token *tok);
char				*get_token_symbol(int token);
t_token				ft_delimit_token(char **index);
t_token				tokenization(char type, char *value);
void				ft_quote(char **s, int *i, char quote_t, _Bool open_q);

#endif
