/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_deploy_maker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/22 11:21:15 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static void	init_deploy_vars(t_deploy *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->flag = 0;
	vars->dash = 0;
	vars->tmp = NULL;
	vars->keep = NULL;
	vars->ptm = NULL;
	vars->range = NULL;
}

static int		range_linker(char *match, t_deploy *var)
{
	if (ft_isalpha(match[var->i]) && ft_isalpha(match[var->i + 2]))
	{
		if (!var->dash)
			var->range = ft_alpharange(match[var->i], match[var->i + 2]);
		else
		{
			var->tmp = ft_alpharange(match[var->i], match[var->i + 2]);
			var->ptm = var->range;
			var->range = ft_strjoin(var->ptm, var->tmp);
			ft_strdel(&var->tmp);
			ft_strdel(&var->ptm);
		}
		var->dash += 1;
		var->flag = 1;
		var->i += 2;
	}
	return (SUCCESS);
}

static int		spread(char *match, t_deploy *var)
{
	while (match[var->i] && match[var->i + 1])
	{
		var->flag = 0;
		if (match[var->i + 1] == DASH)
			range_linker(match, var);
		if (!var->flag)
			var->keep[var->j++] = match[var->i];
		++var->i;
	}
	var->keep[var->j] = '\0';
	return (SUCCESS);
}

static char	*deploy(char *match)
{
	t_deploy	var;

	init_deploy_vars(&var);
	if (!(var.keep = (char*)malloc(sizeof(char) * (ft_strlen(match)))))
		return(0);
	spread(match, &var);
	if (var.range)
	{
		var.tmp = var.keep;
		var.keep = ft_strjoin(var.tmp, var.range);
		ft_strdel(&var.tmp);
		ft_strdel(&var.range);
	}
	return (var.keep);
}

static int	get_btw_square(char **match)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (*match[i] == CL_SQUAR)
	{
		free(*match);
		if (!(*match = ft_strdup(EMPTY_STR)))
			return (0);
		return (SUCCESS);
	}
	if (!(tmp = (char*)ft_memalloc(sizeof(char) * (ft_strlen(*match) + 1))))
		return (0);
	while ((*match)[i] && (*match)[i] != CL_SQUAR)
	{
		tmp[i] = (*match)[i];
		i++;
	}
	tmp[i + 1] = '\0';
	free(*match);
	*match = tmp;
	return (SUCCESS);
}

int		get_deploy(char **match)
{
	int		flag;
	char	*tmp;

	flag = 0;
	tmp = NULL;
	if (ft_isin(DASH, *match))
	{
		tmp = *match;
		*match = deploy(tmp);
		ft_strdel(&tmp);
		flag += 1;
	}
	if (ft_isin(EXCLAM, *match) || ft_isin(CARET, *match))
	{
		tmp = *match;
		*match = ft_strneg(tmp);
		ft_strdel(&tmp);
		flag += 1;
	}
	if (flag == 0)
		get_btw_square(match);
	return (SUCCESS);
}
