/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_double_options1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/02/29 19:11:01 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

static int		test_integers(char **argv, int cmp1, int cmp2)
{
	char	*cmp12;
	char	*cmp21;

	if (!(cmp12 = ft_itoa(cmp1))
	|| !(cmp21 = ft_itoa(cmp2)))
		return (0);
	if ((int)ft_strlen(argv[0]) != (int)ft_strlen(cmp12))
	{
		ft_strdel(&cmp12);
		ft_strdel(&cmp21);
		ft_printf("42sh: test: %s: integer expression expected\n", argv[0]);
		return (E_ERROR);
	}
	else if ((int)ft_strlen(argv[2]) != (int)ft_strlen(cmp21))
	{
		ft_strdel(&cmp12);
		ft_strdel(&cmp21);
		ft_printf("42sh: test: %s: integer expression expected\n", argv[2]);
		return (E_ERROR);
	}
	ft_strdel(&cmp12);
	ft_strdel(&cmp21);
	return (E_SUCCESS);
}

static int		test_integer_cmps(char **argv, char *str)
{
	if (ft_strcmp(str, "==") == E_SUCCESS)
		if (ft_atoi(argv[0]) == ft_atoi(argv[2]))
			return (E_SUCCESS);
	if (ft_strcmp(str, "!=") == E_SUCCESS)
		if (ft_atoi(argv[0]) != ft_atoi(argv[2]))
			return (E_SUCCESS);
	if (ft_strcmp(str, ">") == E_SUCCESS)
		if (ft_atoi(argv[0]) > ft_atoi(argv[2]))
			return (E_SUCCESS);
	if (ft_strcmp(str, ">=") == E_SUCCESS)
		if (ft_atoi(argv[0]) >= ft_atoi(argv[2]))
			return (E_SUCCESS);
	if (ft_strcmp(str, "<") == E_SUCCESS)
		if (ft_atoi(argv[0]) < ft_atoi(argv[2]))
			return (E_SUCCESS);
	if (ft_strcmp(str, "<=") == E_SUCCESS)
		if (ft_atoi(argv[0]) <= ft_atoi(argv[2]))
			return (E_SUCCESS);
	return (E_FAILURE);
}

int				test_d_option_int(char **argv, char *str)
{
	int	cmp1;
	int	cmp2;

	cmp1 = ft_atoi(argv[0]);
	cmp2 = ft_atoi(argv[2]);
	if (test_integers(argv, cmp1, cmp2) == E_FAILURE)
		return (E_FAILURE);
	return ((test_integer_cmps(argv, str) == 0) ? E_SUCCESS : E_FAILURE);
}
