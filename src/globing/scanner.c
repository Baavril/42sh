/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_globing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/26 20:30:28 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"
#include "lexer.h"
#include "shell_variables.h"
#include "builtin_test.h"
#include "expansions.h"
#include "libft.h"

int			scan_current_dir(t_glob *var, char **indepth)
{
	if ((var->dirhandle = opendir(CURRENT_DIR)))
	{
		var->j = 0;
		while ((var->filedata = readdir(var->dirhandle)))
		{
			if (*(var->filedata->d_name) != HIDEN_FILE)
			{
				var->dir[var->j]
				= ft_strdup(pattern_matching(var->filedata->d_name,
				indepth[var->i], GLOBING));
				(!*(var->dir[var->j])) ? free(var->dir[var->j]) : ++var->j;
			}
		}
		var->dir[var->j] = 0;
		closedir(var->dirhandle);
	}
	if (!ft_tablen(var->dir))
		var->nul++;
	return (SUCCESS);
}

static int	dir_paths_constructor(t_glob *var, char **indepth)
{
	if (*(var->filedata->d_name) != HIDEN_FILE)
	{
		free(var->dir[var->x]);
		var->tmp_file = ft_strjoin(var->tmp_dir[var->j], PATH_DIR);
		var->dir[var->x]
		= ft_strjoin(var->tmp_file, pattern_matching(var->filedata->d_name,
		indepth[var->i], GLOBING));
		ft_strdel(&var->tmp_file);
		(!(var->dir[var->x][ft_strpchr(var->dir[var->x], NEXT_DIR) + 1]))
		? free(var->dir[var->x]) : ++var->x;
	}
	return (SUCCESS);
}

int			scan_indepth_dirs(t_glob *var, char **indepth)
{
	var->j = 0;
	var->x = 0;
	ft_tabdel(&var->tmp_dir);
	var->tmp_dir = ft_tabcpy(var->dir);
	while (var->tmp_dir[var->j])
	{
		if ((var->dirhandle = opendir(var->tmp_dir[var->j])))
		{
			while ((var->filedata = readdir(var->dirhandle)))
				dir_paths_constructor(var, indepth);
			closedir(var->dirhandle);
		}
		free(var->dir[var->x]);
		var->dir[var->x] = 0;
		++var->j;
	}
	if (!ft_tablen(var->dir))
		var->nul++;
	return (SUCCESS);
}
