/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:27:13 by bprunev           #+#    #+#             */
/*   Updated: 2020/02/02 18:28:18 by bprunev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "globing.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static int	globing_case(t_pattern *var, char **str, t_checker *elem)
{
	if (elem->flag > 2 && elem->j < elem->len && str[0][elem->j]
	&& (str[0][elem->j] == elem->tmp[elem->i]
	|| str[0][elem->j] == elem->tmp[elem->i] - 32))
	{
		var->c = (str[0][elem->j] == elem->tmp[elem->i])
		? elem->tmp[elem->i] : elem->tmp[elem->i] - 32;
		elem->i = -1;
		++elem->j;
	}
	else if (elem->flag > 2 && !ft_isalpha(str[0][elem->j]))
	{
		if (elem->j < elem->len && ((ft_isprint(str[0][elem->j])
		&& !ft_isalnum(str[0][elem->j]))
		|| (ft_isdigit(str[0][elem->j]) && var->x == 4)))
			++elem->j;
	}
	return (SUCCESS);
}

int			deploy_case(t_pattern *var, char **str, t_checker *elem)
{
	char	c;

	elem->len = ft_strlen(*str);
	while (elem->tmp[elem->i] && elem->len > 0)
	{
		if (elem->flag == 1 && elem->tmp[elem->i] == **str)
		{
			c = elem->tmp[elem->i];
			return (c);
		}
		else if (elem->flag == 2 && elem->tmp[elem->i] == str[0][elem->j])
		{
			c = elem->tmp[elem->i];
			elem->i = -1;
			++elem->j;
		}
		else
			globing_case(var, str, elem);
		++elem->i;
	}
	return (c);
}
