/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_precedence_management1.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/10/18 17:29:13 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** https://www.unix.com/man-page/posix/1posix/test/
 */

#include "../../../../include/builtin_test.h"
#include "../../../../libft/include/libft.h"
#include "../../../../include/builtins.h"

static int	ft_a_management(int ret, int argc, char **args)
{
	int	keep;

	keep = 0;
	if ((keep = return_tests(argc, args)) == e_error)
		return (e_error);
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
	if ((keep = return_tests(argc, args)) == e_error)
		return (e_error);
	return (ret = (keep) ? 1 : 0);
}

static int	test_precedences_management(int argc, char **argv, int ret, char *opts)
{
	int		n;
	int		set;
	char	**args;
	int		*tmp_rets;

	n = 0;
	set = 0;
	if (!(tmp_rets = (int *)malloc(sizeof(int) * (ft_strlen(opts)))))
		return (e_failure);
	while (*opts)
	{
		set = find_next_opt(argv, 1, 1);
		argc = find_next_opt(&argv[argc], 0, 0);
		if (!(args = split_btw_opts(&argv[set], argc)))
			return (e_failure);
		ret = (*opts - 'a' == 0) ? ft_a_management(ret, argc, args)
		: ft_o_management(&tmp_rets[n++], ret, argc, args) ;
		//gestion erreur
		ft_free_tabs(args);
		argv += set;
		opts++;
	}
	return ((ft_tabret(opts, tmp_rets) == e_success) ? e_success: ret);
}

static int	test_first_args(int argc, char **argv)
{
	int		ret;
	char	**args;

	ret = 0;
	if (!(args = split_btw_opts(argv, argc)))
		return (e_failure);
	if ((ret = return_tests(argc, args)) == e_error)
	{
		ft_free_tabs(args);
		return (e_error);
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
	{
		ft_printf("final_ret = %d\n", e_failure);
		return (e_failure);
	}
	if (ft_strcmp("test", argv[0]) == e_success)
		argv++;
	if (ft_manage_parenthesis(&argv[0]) == -1)
	{
		ft_printf("final_ret = %d\n", e_error);
		return (e_error);
	}
	exps = ft_retnbr_opts(argv);
	argc = find_next_opt(argv, 0, 1);
	ret = test_first_args(argc, argv);
	if (exps)
	{
		if (!(opts = ft_ret_optstring(argv, exps)))
			return (e_failure);
		ret = test_precedences_management(argc, argv, ret, opts);
	}
	ft_strdel(&opts);
	ft_printf("final_ret = %d\n", ret);
	return (ret);
}
