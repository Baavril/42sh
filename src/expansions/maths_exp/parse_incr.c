/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_incr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 09:16:12 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/15 15:40:01 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "maths_interne.h"
#include "error.h"

extern char		*g_exptok;

static void		ft_unary_split(t_maths_list *list)
{
	t_maths_list		*sep;
	t_maths_list		*relink;
	t_maths_token		*token;

	sep = NULL;
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
	list->next = (t_maths_list*)ft_lstnew(token, sizeof(t_maths_token));
	list->next->next = relink;
	list->content->prio = ADD_PRIO;
}

int				ft_parse_incr(t_maths_list *list)
{
	t_maths_list		*tmp;
	t_maths_list		*voyager;

	voyager = list;
	if (!(tmp = voyager->next))
		return (voyager->content->prio ? CONV_FAIL : CONV_SUCCESS);
	if (voyager->content->prio == INCR_PRIO && (tmp->content->prio))
		ft_unary_split(voyager);
	while (voyager)
	{
		tmp = voyager;
		voyager = voyager->next;
		if (voyager->content->prio == INCR_PRIO && (tmp->content->prio))
		{
			if (!(tmp = voyager->next))
			{
				psherror(e_missing_operand, g_exptok, e_maths_type);
				return (CONV_FAIL);
			}
			if ((tmp->content->prio))
				ft_unary_split(voyager);
		}
	}
	return (CONV_SUCCESS);
}

void			ft_interpret_incr(t_maths_list *list)
{
	t_maths_list		*tmp;
	t_maths_list		*voyager;

	voyager = list;
	tmp = voyager->next;
	if (voyager->content->prio == INCR_PRIO && !(tmp->content->prio))
		voyager->content->prio == PREINCR_PRIO;
	while (voyager)
	{
		voyager = voyager->next;
		if (voyager->content->prio == INCR_PRIO && !(tmp->content->prio))
			voyager->content->prio == PREINCR_PRIO;
	}
}
