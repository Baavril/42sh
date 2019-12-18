/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunevi <bprunevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:26:31 by bprunevi          #+#    #+#             */
/*   Updated: 2019/12/18 12:59:59 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "builtins.h"
#include "hash_module.h"
#include <sys/stat.h>
#include <unistd.h>

int				is_regfile(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

char			*path_join(char *str1, char *str2)
{
	char *rtn;

	rtn = malloc(ft_strlen(str1) + ft_strlen(str2) + 2);
	ft_strcpy(rtn, str1);
	ft_strcat(rtn, "/");
	ft_strcat(rtn, str2);
	return (rtn);
}

char	**ft_agetenv(char *name)
{
	extern char **environ;
	int i;
	int j;

	i = -1;
	if (environ)
		while (environ[++i] && !(j = 0))
			while (name[j] == environ[i][j])
				if (environ[i][++j] == '=' && !name[j])
					return (&environ[i]);
	return (NULL);
}

char *check_bin(char **argv)
{
	char	**path;
	char	**path_split;
	char	*tmp;
	int		i;

	i = -1;
	if ((path = ft_agetenv("PATH")))
	{
		path_split = ft_strsplit(&(*path)[5], ':');
		while (path_split[++i])
		{
			if ((tmp = path_join(path_split[i], *argv)) && !access(tmp, X_OK) && is_regfile(tmp))
			{
				ft_tabdel(&path_split);
				return (tmp);
			}
			ft_strdel(&tmp);
		}
		ft_tabdel(&path_split);
	}
	return (NULL);
}

int  eval_command(char **arg)
{
	char *absolute_path;
	extern t_htable *g_bintable;

	if (!access(*arg, X_OK) && is_regfile(*arg))
		return(0);
	if (ft_inbintable(*arg, &absolute_path, HIT))
	{
		if (!access(absolute_path, X_OK) && is_regfile(absolute_path))
		{
			ft_strdel(arg);
			*arg = absolute_path;
			return(0);
		}
		ft_del_entry(g_bintable, absolute_path);
	}
	if ((absolute_path = check_bin(arg)))
	{
		if (!access(absolute_path, X_OK) && is_regfile(absolute_path))
		{
			ft_insert_bintable(*arg, absolute_path, 1);
			ft_strdel(arg);
			*arg = absolute_path;
			return(0);
		}
	}
	return(1);
}

