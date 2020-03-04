/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:40:01 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/29 16:03:50 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# include "libft.h"
# include "input.h"

# define ENTER '\n'
# define BACKSPACE '\177'
# define TABULATION '\t'

int			delete_key(char **buff, t_cursor *cursor);
int			backspace_key(char **buff, t_cursor *cursor);
int			tab_key(char **buff, t_cursor *cursor);
int			normal_char(char **buff, t_cursor *cursor, char c);
char		*get_history(char **buff, t_cursor *cursor);
int			select_key(char **buff, t_cursor *cursor);
int			paste_key(char **buff, t_cursor *cursor);
int			escape_char(char **buff, t_cursor *cursor, char *str);
int			previous_word(char **buff, t_cursor *cursor);
int			next_word(char **buff, t_cursor *cursor);
int			end_key(char **buff, t_cursor *cursor);
int			home_key(char **buff, t_cursor *cursor);
int			paste_key(char **buff, t_cursor *cursor);
int			up_arrow(char **buff, t_cursor *cursor);
int			down_arrow(char **buff, t_cursor *cursor);
int			delete_key(char **buff, t_cursor *cursor);
int			left_arrow(char **buff, t_cursor *cursor);
int			right_arrow(char **buff, t_cursor *cursor);
int			set_string(char **buff, t_cursor *cursor, char *str);
char		*buff_realloc(char *old_buff, size_t i);

#endif
