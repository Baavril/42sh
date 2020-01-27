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
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static int		launch_deploy(char **str, char *match, char flag)
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

static int	neg_deploy_case(char *ptm, char **str)
{
	int	i;

	i = 0;
	while (ptm && ptm[i])
	{
		if (ptm[i] == **str)
		{
			++(*str);
			i = -1;
		}
		++i;
	}
	return (SUCCESS);
}

static int	deploy_case(char *tmp, int *ret, char **str, int flag)
{
	int i;
	int j;
	char c;
	int len;

	i = 0;
	c = 0;
	len = ft_strlen(*str);
	while (tmp[i] && len > 0)
	{
		if (flag == 1 && tmp[i] == **str)
		{
			while (c != tmp[i])
				c++;
			return (c);
		}
		else if (flag == 2 && tmp[i] == **str)
		{
			(*str)++;
			c = tmp[i];
			i = -1;
			++(*ret);
		}
		else if (flag > 2)
		{
			j = 0;
			while (j < len && str[0][j])
			{
				if (str[0][j] == tmp[i])
				{
					c = tmp[i];
					return (c);
				}
				++j;
			}
		}
		++i;
	}
	return (c);
}

int		check_deploy(char *str, char *match, int flag, int star)
{
	char	c;
	int		ret;
	char	*tmp;
	char	*ptm;

	c = 0;
	ret = 0;
	tmp = NULL;
	ptm = NULL;
	if ((int)ft_strlen(str) <= 0)
		return (ret);
	if (star && (match[0] == CARET || match[1] == CARET))
		launch_deploy(&ptm, match, CARET);
	if (match[0] == OP_SQUAR)
		launch_deploy(&tmp, match, OP_SQUAR);
	neg_deploy_case(ptm, &str);
	if ((c = deploy_case(tmp, &ret, &str, flag)))
	{
		free_tmp_vars(&tmp, &ptm);
		return (c);
	}
	free_tmp_vars(&tmp, &ptm);
	return ((ret) ? c : ERROR);
}
