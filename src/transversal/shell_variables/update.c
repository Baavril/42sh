/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by baavril           #+#    #+#             */
/*   Updated: 2019/12/03 16:21:55 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "shell_variables.h"
#include "libft.h"
#include "prompt.h"

struct s_svar	*g_svar;

int				update_prompt_var(void)
{
	char			*tmp;
	struct s_svar	*voyager;

	mkprompt(&tmp);
	voyager = g_svar;
	while (voyager)
	{
		if (!(ft_strcmp(voyager->key, PS1)))
		{
			ft_strdel(&voyager->value);
			voyager->value = ft_strdup(tmp);
			ft_strdel(&tmp);
			return (0);
		}
		voyager = voyager->next;
	}
	ft_strdel(&tmp);
	return (0);
}
