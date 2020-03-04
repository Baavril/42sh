/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_precedence_management2.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2019/10/18 17:29:13 by bprunev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

static int	ft_error_parenthesis(int j, int ret)
{
	if (j && !ret)
	{
		ft_putendl("42sh: test: `)' expected");
		return (-1);
	}
	return (0);
}

static int	ft_check_parenthesis(char **argv, int i, int j)
{
	int	ret;

	ret = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "(") == E_SUCCESS)
		{
			j = i + 1;
			while (argv[j])
			{
				if (ft_strcmp(argv[j], "-o") == E_SUCCESS)
					argv[j][1] = 'a';
				if (ft_strcmp(argv[j], ")") == E_SUCCESS)
				{
					ret++;
					break ;
				}
				j++;
			}
		}
		i++;
	}
	return ((ft_error_parenthesis(j, ret) != E_SUCCESS) ? -1 : ret);
}

int			ft_manage_parenthesis(char **argv)
{
	int	i;
	int	j;
	int	ret;
	int	keep;

	i = 0;
	j = 0;
	keep = 0;
	if ((ret = ft_check_parenthesis(&argv[0], i, j)) > 0)
	{
		while (argv[i])
		{
			if ((ft_strcmp(argv[i], "(") == E_SUCCESS
			|| ft_strcmp(argv[i], ")") == E_SUCCESS) && argv[i + 1])
				i++;
			if (!(argv[j] = ft_strdup(argv[i])))
				return (E_ERROR);
			j++;
			i++;
		}
		keep = ft_delalloc(argv, ret);
	}
	return ((ret == -1) ? ret : keep);
}
