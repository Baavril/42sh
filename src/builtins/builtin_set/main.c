/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:21:48 by bprunev           #+#    #+#             */
/*   Updated: 2020/02/29 19:22:53 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "shell_variables.h"
#include "libft.h"

extern struct s_svar	*g_svar;
extern struct s_pos		*g_pos;

static void				prtlist(void)
{
	struct s_svar	*voyager;

	voyager = g_svar;
	while (g_svar)
	{
		printf("%s\n", ((char*)g_svar->str));
		g_svar = g_svar->next;
	}
	g_svar = voyager;
}

static void				free_pos_list(void)
{
	struct s_pos	*tmp1;

	while (g_pos)
	{
		tmp1 = g_pos->next;
		ft_strdel(&(g_pos->str));
		ft_strdel(&(g_pos->key));
		ft_strdel(&(g_pos->value));
		free(g_pos);
		g_pos = tmp1;
	}
}

int						cmd_set(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (argc == 1)
		prtlist();
	else
	{
		free_pos_list();
		set_positional_params(argv);
	}
	return (0);
}
