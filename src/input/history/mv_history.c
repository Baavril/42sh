/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:58:02 by yberramd          #+#    #+#             */
/*   Updated: 2020/02/29 16:01:07 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int	ft_swap_2(t_history **history, char *cmd)
{
	ft_strdel(&(*history)->str);
	if (!((*history)->str = ft_strdup(cmd)))
		return (-1);
	return (1);
}

int	get_first(t_history **history, char **cmd)
{
	while ((*history)->previous)
		(*history) = (*history)->previous;
	*cmd = (*history)->str;
	return (1);
}

int	get_last(t_history **history, char **cmd)
{
	while ((*history)->next)
		(*history) = (*history)->next;
	*cmd = (*history)->str;
	return (1);
}

int	get_next(t_history **history, char **cmd)
{
	if ((*history)->next)
	{
		(*history) = (*history)->next;
		*cmd = (*history)->str;
		return (1);
	}
	else
	{
		*cmd = (*history)->str;
		return (2);
	}
}

int	get_previous(t_history **history, char **cmd)
{
	if ((*history)->previous)
	{
		(*history) = (*history)->previous;
		*cmd = (*history)->str;
		return (1);
	}
	else
	{
		*cmd = (*history)->str;
		return (2);
	}
}
