/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_deploy_launcher.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/26 19:59:48 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "globing.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

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

static int	deploy_case(t_pattern *var, char *tmp, char **str, int flag)
{
	int		i;
	int		j;
	char	c;
	int		len;

	i = 0;
	c = 0;
	j = 0;
	len = ft_strlen(*str);
	while (tmp[i] && len > 0)
	{
		if (flag == 1 && tmp[i] == **str)
		{
			c = tmp[i];
			return (c);
		}
		else if (flag == 2 && tmp[i] == str[0][j])
		{
			c = tmp[i];
			i = -1;
			++j;
		}
		else if (flag > 2 && j < len && str[0][j] && (str[0][j] == tmp[i] || str[0][j] == tmp[i] - 32))
		{
			c = (str[0][j] == tmp[i]) ? tmp[i] : tmp[i] - 32;
			i = -1;
			++j;
		}
		else if (flag > 2 && !ft_isalpha(str[0][j]))
		{
			if (j < len && ((ft_isprint(str[0][j]) && !ft_isalnum(str[0][j]))
			|| (ft_isdigit(str[0][j]) && var->x == 4)))
				++j;
		}
		if (j == len)
			break ;
		++i;
	}
	return (c);
}

int		check_deploy(char *str, char *match, int flag, t_pattern *var)
{
	char	c;
	char	*tmp;
	char	*ptm;

	c = 0;
	tmp = NULL;
	ptm = NULL;
	if ((int)ft_strlen(str) <= 0)
		return (0);
	if (var->x == 4 && (match[0] == CARET || match[1] == CARET))
		launch_deploy(&ptm, match, CARET);
	if (match[0] == OP_SQUAR)
		launch_deploy(&tmp, match, OP_SQUAR);
	neg_deploy_case(var, ptm, &str);
	if ((c = deploy_case(var, tmp, &str, flag)))
	{
		free_tmp_vars(&tmp, &ptm);
		return (c);
	}
	free_tmp_vars(&tmp, &ptm);
	return (ERROR);
}
