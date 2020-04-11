/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 15:48:33 by bprunevi          #+#    #+#             */
/*   Updated: 2019/09/29 11:20:01 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

# define INHIB		"[]{}()\'\""
# define OPEN		"[{("
# define CLOSE		"]})"
# define QUOTES		"\'\""


int			quote_prompt(t_list **unclosed_inhib, char *command);

#endif
