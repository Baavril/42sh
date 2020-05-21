/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 15:48:33 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/21 14:30:49 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

# define INHIB		"[]{}()\'\""
# define OPEN		"[{("
# define CLOSE		"]})"
# define QUOTES		"\'\""
# define ERR		0
# define NO_ERR		1
# define ESC_NL		2

void		ft_lst_strdel(void *content, size_t content_size);
int			quote_prompt(t_list **unclosed_inhib, char *command);
int			ft_treat_inhib(t_list **unclosed_inhib, char inhib);
char			*mkprompt_expand(const char *ps1, size_t *len);

#endif
