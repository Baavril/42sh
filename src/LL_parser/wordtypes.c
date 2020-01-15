/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:29:21 by yberramd          #+#    #+#             */
/*   Updated: 2020/01/15 12:02:51 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"

char	*filename(t_token tok)
{
	return(word(tok)); /* Apply rule 2*/
}

char	*here_end(t_token tok)
{
	return(word(tok)); /* Apply rule 3*/
}

char	*cmd_name(t_token tok)
{
	return(word(tok)); /* Apply rule 7a*/
}

char	*cmd_word(t_token tok)
{
	return(word(tok)); /* Apply rule 7b*/
}
