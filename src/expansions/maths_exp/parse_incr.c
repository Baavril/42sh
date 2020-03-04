/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_incr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 09:16:12 by bprunevi          #+#    #+#             */
/*   Updated: 2020/02/12 11:48:37 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "maths_expansion.h"
#include "error.h"

extern char		*g_exptok;

static void		ft_unary_split(t_maths_list *list)
{
	t_maths_list		*relink;
	t_maths_token		token;

	relink = list->next;
	if (!ft_strcmp(list->content->token, "++"))
	{
		free(list->content->token);
		list->content->token = ft_strdup("+");
		token = ft_init_maths_token("+", 1, IS_OP);
	}
	else if (!ft_strcmp(list->content->token, "--"))
	{
		free(list->content->token);
		list->content->token = ft_strdup("-");
		token = ft_init_maths_token("-", 1, IS_OP);
	}
	else
		return ;
	list->next = (t_maths_list*)ft_lstnew(&token, sizeof(token));
	list->next->next = relink;
	list->content->prio = ADD_PRIO;
}

static void		ft_unary_analysis(t_maths_list *list)
{
	char			*tok;
	char			*nextok;
	t_maths_token	*next;

	next = list->next->content;
	tok = list->content->token;
	nextok = next->token;
	if (next->prio == ADD_PRIO)
	{
		if (*nextok == *tok)
		{
			list->next->content = list->content;
			list->content = next;
		}
	}
	else
		ft_unary_split(list);
}

int				ft_parse_incr(t_maths_list *list)
{
	t_maths_list		*tmp;
	t_maths_list		*voyager;

	voyager = list;
	if (!(tmp = voyager->next))
		return (voyager->content->prio ? CONV_FAIL : CONV_SUCCESS);
	if (voyager->content->prio == INCR_PRIO && (tmp->content->prio))
		ft_unary_analysis(voyager);
	while (voyager)
	{
		tmp = voyager;
		if (!(voyager = voyager->next))
			break ;
		if (voyager->content->prio == INCR_PRIO && (tmp->content->prio))
		{
			if (!(tmp = voyager->next))
			{
				psherror(e_missing_operand, g_exptok, e_maths_type);
				return (CONV_FAIL);
			}
			if ((tmp->content->prio))
				ft_unary_analysis(voyager);
		}
	}
	return (CONV_SUCCESS);
}
