/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:24:31 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/15 16:46:14 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_interne.h"
#include "error.h"

extern char		*g_exptok;

int				ft_is_varname(const char *token)
{
	if (ft_isdigit(*token))
		return (0);
	while (*token)
	{
		if (!(ft_isalnum(*token) || *token == '_'))
			return (0);
		token++;
	}
	return (1);
}

static int		ft_parse_assign(t_maths_list *list)
{
	t_maths_list	*tmp;
	int				i;

	i = 0;
	while (list)
	{
		tmp = list;
		if (list && ++i)
			list = list->next;
		if (list && list->content->prio == ASSIGN_PRIO)
		{
			if (i != 1)
			{
				psherror(e_assign_nonvar, g_exptok, e_maths_type);
				return (CONV_FAIL);
			}
			if (!ft_is_varname(tmp->content->token))
			{
				psherror(e_invalid_name, g_exptok, e_maths_type);
				return (CONV_FAIL);
			}
			list = list->next;
			while (list && list->content->prio < ASSIGN_PRIO)
				list = list->next;
			if (list && list->content->prio == ASSIGN_PRIO)
			{
				psherror(e_assign_nonvar, g_exptok, e_maths_type);
				return (CONV_FAIL);
			}
			i = 0;
		}
	}
	return (CONV_SUCCESS);
}

int				ft_maths_parser(t_maths_list *list)
{
	if (!list)
		return (CONV_SUCCESS);
	if (ft_parse_assign(list) == CONV_FAIL)
		return (CONV_FAIL);
//	if (ft_parse_incr(list) == CONV_FAIL)
//		return (CONV_FAIL);
//	ft_interpret_incr(list);
	return (CONV_SUCCESS);
}
