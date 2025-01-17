/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:18:14 by tgouedar          #+#    #+#             */
/*   Updated: 2020/02/19 12:14:56 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_expansion.h"

static void		ft_equivalent_add(t_maths_list *list)
{
	t_maths_list	*voyager;
	t_maths_list	*relink;
	int				inf;

	inf = 0;
	relink = list;
	while (relink && relink->content->prio == ADD_PRIO)
	{
		voyager = relink;
		if (*(voyager->content->token) == '-')
			inf++;
		relink = relink->next;
	}
	voyager->next = NULL;
	free(list->content->token);
	list->content->token = ft_strdup((inf % 2) ? "-" : "+");
	voyager = list->next;
	list->next = relink;
	ft_lstdel((t_list**)(&voyager), &ft_free_maths_token);
}

void			ft_parse_sign(t_maths_list *list)
{
	while (list)
	{
		if (list->content->prio == ADD_PRIO)
			ft_equivalent_add(list);
		list = list->next;
	}
}

void			ft_parse_neg_prio(t_maths_list *list)
{
	t_maths_list	*voyager;

	voyager = list;
	while (voyager->next)
	{
		voyager = voyager->next;
		if (list->content->prio < ADD_PRIO && list->content->prio > 0
		&& voyager->content->prio == ADD_PRIO)
			voyager->content->prio = NEG_PRIO;
		list = voyager;
	}
}
