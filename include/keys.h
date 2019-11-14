/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:40:01 by bprunevi          #+#    #+#             */
/*   Updated: 2019/11/12 18:33:18 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

#include "libft.h"
#include "input.h"

# define ENTER '\n'
# define BACKSPACE '\177'
# define TABULATION '\t'

void search_history(char **buff, t_cursor *cursor);
void delete_key(char **buff, t_cursor *cursor);
void backspace_key(char **buff, t_cursor *cursor);
void tab_key(char **buff, t_cursor *cursor);
void normal_char(char **buff, t_cursor *cursor, char c);
void select_key(char **buff, t_cursor *cursor);
void paste_key(char **buff, t_cursor *cursor);
void escape_char(char **buff, t_cursor *cursor, char *str);
void previous_word(char **buff, t_cursor *cursor);
void next_word(char **buff, t_cursor *cursor);
void end_key(char **buff, t_cursor *cursor);
void home_key(char **buff, t_cursor *cursor);
void paste_key(char **buff, t_cursor *cursor);
void up_arrow(char **buff, t_cursor *cursor);
void down_arrow(char **buff, t_cursor *cursor);
void delete_key(char **buff, t_cursor *cursor);
void left_arrow(char **buff, t_cursor *cursor);
void right_arrow(char **buff, t_cursor *cursor);
void set_string(char **buff, t_cursor *cursor, char *str);
char	*buff_realloc(char *old_buff, size_t i);

#endif
