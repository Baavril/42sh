/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:29:21 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/26 16:14:02 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"

char	*filename(t_token tok)
{
	return (word(tok));
}

char	*here_end(t_token tok)
{
	return (word(tok));
}

char	*cmd_name(t_token tok)
{
	return (word(tok));
}

char	*cmd_word(t_token tok)
{
	return (word(tok));
}
