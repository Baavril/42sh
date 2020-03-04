/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/03/02 18:05:39 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"
#include "lexer.h"
#include "shell_variables.h"
#include "builtin_test.h"
#include "expansions.h"
#include "libft.h"

static void	init_glob_var(t_glob *var)
{
	var->i = 0;
	var->j = 0;
	var->x = 0;
	var->n = 0;
	var->f = 0;
	var->nul = 0;
	var->dir = NULL;
	var->ret = NULL;
	var->tmp_dir = NULL;
	var->free_dir = NULL;
	var->tmp_file = NULL;
	var->filedata = NULL;
	var->dirhandle = NULL;
}

static char	**ret_token(char **ptm, char *token)
{
	ptm = (char**)malloc(sizeof(char*) * 2);
	ptm[0] = ft_strdup(token);
	ptm[1] = 0;
	return (ptm);
}

static int	set_tab_ret(t_glob *var)
{
	var->n = 0;
	if (!var->nul)
	{
		if (!(var->ret =
					(char**)ft_memalloc(sizeof(char*)
						* (ft_tablen(var->dir) + 1))))
			return (ERROR);
		while (var->dir[var->n])
		{
			var->ret[var->n] = ft_strdup(var->dir[var->n]);
			++var->n;
		}
		var->ret[var->n] = 0;
		sort_ascii_tab(var->ret);
		ft_tabdel(&var->dir);
		ft_tabdel(&var->tmp_dir);
		return (SUCCESS);
	}
	return (ERROR);
}

char		**globing(char **indepth, char *token)
{
	t_glob	var;

	init_glob_var(&var);
	if (!indepth[0])
		return (ret_token(var.ret, token));
	if (!(var.dir = (char **)ft_memalloc(sizeof(char *) * MAX_DIR)))
		return (NULL);
	while (indepth[var.i])
	{
		if (!(var.i))
			scan_current_dir(&var, indepth);
		else
			scan_indepth_dirs(&var, indepth);
		++var.i;
	}
	if (set_tab_ret(&var) == SUCCESS)
		return (var.ret);
	ft_tabdel(&var.dir);
	ft_tabdel(&var.tmp_dir);
	return ((var.nul) ? ret_token(var.ret, token) : var.ret);
}
