/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_deploy_launcher.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/02/02 18:28:36 by bprunev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "globing.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static void	init_elems(t_checker *elem)
{
	elem->i = 0;
	elem->j = 0;
	elem->c = 0;
	elem->len = 0;
	elem->flag = 0;
	elem->tmp = NULL;
	elem->ptm = NULL;
}

static int	launch_deploy(char **str, char *match, char flag)
{
	if (!(*str = ft_strdupto(match + (ft_strpchr(match, flag) + 1), CL_SQUAR)))
		return (ERROR);
	get_deploy(str);
	return (SUCCESS);
}

static void	free_tmp_vars(char **tmp, char **ptm)
{
	if (tmp)
		ft_strdel(tmp);
	if (ptm)
		ft_strdel(ptm);
}

static int	neg_deploy_case(t_pattern *var, char *ptm, char **str)
{
	int	i;

	i = 0;
	while (ptm && ptm[i])
	{
		if (ptm[i] == **str)
		{
			var->i++;
			++(*str);
			i = -1;
		}
		++i;
	}
	return (SUCCESS);
}

int			check_deploy(char *str, char *match, int flag, t_pattern *var)
{
	t_checker	elem;

	init_elems(&elem);
	if ((int)ft_strlen(str) <= 0)
		return (0);
	elem.flag = flag;
	if (!ft_isin(DASH, match) && ft_strlen(match) == 3)
	{
		elem.c = match[1];
		return (elem.c);
	}
	if (var->x == 4 && (match[0] == CARET || match[1] == CARET))
		launch_deploy(&elem.ptm, match, CARET);
	if (match[0] == OP_SQUAR)
		launch_deploy(&elem.tmp, match, OP_SQUAR);
	neg_deploy_case(var, elem.ptm, &str);
	if ((elem.c = deploy_case(var, &str, &elem)))
	{
		free_tmp_vars(&elem.tmp, &elem.ptm);
		return (elem.c);
	}
	free_tmp_vars(&elem.tmp, &elem.ptm);
	return (ERROR);
}
