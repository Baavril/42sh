/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 15:48:33 by bprunevi          #+#    #+#             */
/*   Updated: 2020/05/22 12:01:37 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

# define INHIB			"[]{}()\'\"#\n"
# define OPEN			"[{(#"
# define CLOSE			"]})"
# define QUOTES			"\'\""
# define INHIB_COM		"\'\"{("
# define ERR			0
# define NO_ERR			1
# define ESC_NL			2

void		ft_lst_strdel(void *content, size_t content_size);
int			quote_prompt(t_list **unclosed_inhib, char *command);
int			ft_treat_inhib(t_list **unclosed_inhib, char inhib);
void		ft_inhib_exception(t_list **unclosed_inhib,
									char **command, char open);

#endif
