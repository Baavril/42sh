/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:40:01 by bprunevi          #+#    #+#             */
/*   Updated: 2019/10/20 11:41:00 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
#define KEYS_H
#include "libft.h"

void delete_key(char **buff, size_t *j, size_t *i);
void backspace_key(char **buff, size_t *j, size_t *i);
void tab_key(char **buff, size_t *j, size_t *i);
void normal_char(char **buff, size_t *j, size_t *i, char c);
void select_key(char **buff, size_t *j, size_t *i, size_t *u);
void paste_key(char **buff, size_t *j, size_t *i);
void escape_char(char **buff, size_t *j, size_t *i, size_t *u);

#endif
