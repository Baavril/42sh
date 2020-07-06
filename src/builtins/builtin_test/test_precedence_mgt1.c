/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_precedence_mgt1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/07/06 13:09:05 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** https://www.unix.com/man-page/posix/1posix/test/
*/

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

static int	ft_a_management(int ret, int argc, char **args)
{
	int	keep;

	keep = 0;
	if ((keep = return_tests(argc, args)) == E_ERROR)
		return (E_ERROR);
	return (ret = (keep) ? 1 : ret + 0);
}

static int	ft_o_management(int *tmp_rets, int ret, int argc, char **args)
{
	int	n;
	int	keep;

	n = 0;
	keep = 0;
	tmp_rets[n] = ret;
	n++;
	if ((keep = return_tests(argc, args)) == E_ERROR)
		return (E_ERROR);
	return (ret = (keep) ? 1 : 0);
}

/*
** Manque gestion erreur <<<<< CECI EST UN MODULE TERMINE !
** Bien joue les gars...
*/

static int	test_precedences_management(int argc, char **argv, int ret,
																	char *opts)
{
	int		n;
	int		set;
	char	**args;
	int		*tmp_rets;

	n = 0;
	set = 0;
	if (!(tmp_rets = (int *)malloc(sizeof(int) * (ft_strlen(opts)))))
		return (E_FAILURE);
	while (*opts)
	{
		set = find_next_opt(argv, 1, 1);
		argc = find_next_opt(&argv[argc], 0, 0);
		if (!(args = split_btw_opts(&argv[set], argc)))
			return (E_FAILURE);
		ret = (*opts - 'a' == 0) ? ft_a_management(ret, argc, args)
						: ft_o_management(&tmp_rets[n++], ret, argc, args);
		ft_free_tabs(args);
		argv += set;
		opts++;
	}
	return ((ft_tabret(opts, tmp_rets) == E_SUCCESS) ? E_SUCCESS : ret);
}

static int	test_first_args(int argc, char **argv)
{
	int		ret;
	char	**args;

	ret = 0;
	if (!(args = split_btw_opts(argv, argc)))
		return (E_FAILURE);
	if ((ret = return_tests(argc, args)) == E_ERROR)
	{
		ft_free_tabs(args);
		return (E_ERROR);
	}
	ft_free_tabs(args);
	return (ret);
}

int			cmd_test(int argc, char **argv)
{
	int		ret;
	int		exps;
	char	*opts;

	ret = 1;
	exps = 0;
	opts = NULL;
	if (argc == 1)
		return (E_FAILURE);
	if (ft_strcmp("test", argv[0]) == E_SUCCESS)
		argv++;
	if (ft_manage_parenthesis(&argv[0]) == -1)
		return (E_ERROR);
	exps = ft_retnbr_opts(argv);
	argc = find_next_opt(argv, 0, 1);
	ret = test_first_args(argc, argv);
	if (exps)
	{
		if (!(opts = ft_ret_optstring(argv, exps)))
			return (E_FAILURE);
		ret = test_precedences_management(argc, argv, ret, opts);
	}
	ft_strdel(&opts);
	return (ret);
}
