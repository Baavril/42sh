/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 21:13:34 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/18 14:15:18 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

struct s_var	*g_svar;

int			new_history(t_history **history)
{
	if (history != NULL && (*history) != NULL)
	{
		while ((*history)->next != NULL)
			(*history) = (*history)->next;
	}
	return (1);
}

void		assign_max_home(int *max, char **home)
{
	char	*nbr;

	nbr = getshvar(HISTSIZE);
	if (nbr != NULL)
		*max = ft_atoi(nbr);
	ft_strdel(&nbr);
	*home = getshvar(HISTFILE);
}
