/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_precedence_management2.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/10/18 17:29:13 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/builtin_test.h"
#include "../../../../libft/include/libft.h"
#include "../../../../include/builtins.h"

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
		if (ft_strcmp(argv[i], "(") == e_success)
		{
			j = i + 1;
			while (argv[j])
			{
				if (ft_strcmp(argv[j], "-o") == e_success)
					argv[j][1] = 'a';
				if (ft_strcmp(argv[j], ")") == e_success)
				{
					ret++;
					break ;
				}
				j++;
			}
		}
		i++;
	}
	return ((ft_error_parenthesis(j, ret) != e_success) ? -1 : ret);
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
			if ((ft_strcmp(argv[i], "(") == e_success
			|| ft_strcmp(argv[i], ")") == e_success) && argv[i + 1])
				i++;
			if (!(argv[j] = ft_strdup(argv[i])))
				return (e_error);
			j++;
			i++;
		}
		keep = ft_delalloc(argv, ret);
	}
	return ((ret == -1) ? ret : keep);
}
