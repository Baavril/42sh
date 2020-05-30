/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:53 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/30 19:02:34 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "tokens.h"

int					ft_istoken(char *str);
int					ft_is_quote(char c);
struct s_token		get_next_token(char *str);
t_token				get_next_token_alias(char *str);
void				ft_free_token(t_token *tok);
void				*cpy_without_bn(void *dst, const void *src, size_t n);
char				*get_token_symbol(int token);
t_token				ft_delimit_token(char **index);
t_token				tokenization(char type, char *value);
void				ft_quote(char **s, int *i, char quote_t, _Bool open_q);

#endif
