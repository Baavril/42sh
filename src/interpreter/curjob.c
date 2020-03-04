/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curjob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:08:53 by bprunevi          #+#    #+#             */
/*   Updated: 2020/03/04 13:59:48 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcont.h"
#include "curjob.h"

int (*g_flist[])(t_elem left, t_elem right) =
{
	&i_less,
	&i_dless,
	&i_lessand,
	&i_great,
	&i_dgreat,
	&i_greatand,
	&i_lessgreat,
	&i_dlessdash,
	&i_clobber,
	&i_andgreat,
	&i_and_op,
	&i_or_op,
	&i_pipe_sequence,
};

char g_flist_name[14][4] =
{
	"<",
	"<<",
	"<&",
	">",
	">>",
	">&",
	"<>",
	"<<-",
	">|",
	"&>",
	"&&",
	"||",
	"|",
};

int				curjob_cat(char *str)
{
	extern t_job	g_curjob;
	char			*tmp;

	tmp = g_curjob.cmd;
	if (!g_curjob.cmd)
		g_curjob.cmd = ft_strdup(str);
	else
	{
		g_curjob.cmd = ft_strnjoin(3, g_curjob.cmd, " ", str);
		free(tmp);
	}
	return (0);
}

int				curjob_add(t_node *node)
{
	int i;

	i = -1;
	while (g_flist[++i])
		if (node->f == g_flist[i])
			curjob_cat(g_flist_name[i]);
	return (0);
}
