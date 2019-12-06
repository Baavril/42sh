/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
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

void	prtlist()
{
	struct s_svar *voyager;

	voyager = g_svar;
	while (g_svar)
	{
		printf("%s\n", ((char*)g_svar->str));
		g_svar = g_svar->next;
	}
	g_svar = voyager;
}

int cmd_set(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	prtlist();
	return (0);
}
