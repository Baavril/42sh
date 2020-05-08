/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 21:13:34 by yberramd          #+#    #+#             */
/*   Updated: 2020/05/07 21:16:11 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int	new_history(t_history **history)
{
	if (history != NULL && (*history) != NULL)
	{
		while ((*history)->next != NULL)
			(*history) = (*history)->next;
	}
	return (1);
}
