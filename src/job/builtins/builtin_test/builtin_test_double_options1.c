/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_double_options1.c                     :+:      :+:    :+:   */
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

static int		test_integers(char **argv, int cmp1, int cmp2)
{
	char	*cmp12;
	char	*cmp21;

	if (!(cmp12 = ft_itoa(cmp1)) || !(cmp21 = ft_itoa(cmp2)))
		return (0);
	if ((int)ft_strlen(argv[0]) != (int)ft_strlen(cmp12))
	{
		ft_strdel(&cmp12);
		ft_strdel(&cmp21);
		ft_printf("42sh: test: %s: integer expression expected\n", argv[0]);
		return (e_error);
	}
	else if ((int)ft_strlen(argv[2]) != (int)ft_strlen(cmp21))
	{
		ft_strdel(&cmp12);
		ft_strdel(&cmp21);
		ft_printf("42sh: test: %s: integer expression expected\n", argv[2]);
		return (e_error);
	}
	ft_strdel(&cmp12);
	ft_strdel(&cmp21);
	return (e_success);
}

static int		test_integer_cmps(char **argv, char *str)
{
	if (ft_strcmp(str, "==") == e_success)
		if (ft_atoi(argv[0]) == ft_atoi(argv[2]))
			return (e_success);
	if (ft_strcmp(str, "!=") == e_success)
		if (ft_atoi(argv[0]) != ft_atoi(argv[2]))
			return (e_success);
	if (ft_strcmp(str, ">") == e_success)
		if (ft_atoi(argv[0]) > ft_atoi(argv[2]))
			return (e_success);
	if (ft_strcmp(str, ">=") == e_success)
		if (ft_atoi(argv[0]) >= ft_atoi(argv[2]))
			return (e_success);
	if (ft_strcmp(str, "<") == e_success)
		if (ft_atoi(argv[0]) < ft_atoi(argv[2]))
			return (e_success);
	if (ft_strcmp(str, "<=") == e_success)
		if (ft_atoi(argv[0]) <= ft_atoi(argv[2]))
			return (e_success);
	return (e_failure);
}

int				test_d_option_int(char **argv, char *str)
{
	int	cmp1;
	int	cmp2;

	cmp1 = ft_atoi(argv[0]);
	cmp2 = ft_atoi(argv[2]);
	if (test_integers(argv, cmp1, cmp2) == e_failure)
		return (e_failure);
	return ((test_integer_cmps(argv, str) == 0) ? e_success : e_failure);
}
