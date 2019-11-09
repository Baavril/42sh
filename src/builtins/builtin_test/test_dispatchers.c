/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_dispatchers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2019/11/09 11:47:27 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

t_test_s_opt	g_test_s_opt[] =
{
	{"a", &test_s_option_a},
	{"b", &test_s_option_b},
	{"c", &test_s_option_c},
	{"d", &test_s_option_d},
	{"e", &test_s_option_a},
	{"f", &test_s_option_f},
	{"g", &test_s_option_g},
	{"h", &test_s_option_h},
	{"k", &test_s_option_k},
	{"n", &test_s_option_n},
	{"o", &test_s_option_o},
	{"p", &test_s_option_p},
	{"r", &test_s_option_r},
	{"s", &test_s_option_s},
	{"t", &test_s_option_t},
	{"u", &test_s_option_u},
	{"v", &test_s_option_v},
	{"w", &test_s_option_w},
	{"x", &test_s_option_x},
	{"z", &test_s_option_z},
	{"L", &test_s_option_h},
	{"O", &test_s_option_O},
	{"N", &test_s_option_N},
	{"G", &test_s_option_G},
	{"S", &test_s_option_S}
};

t_test_d_opt	g_test_d_opt[] =
{
	{"eq", &test_d_option_int},
	{"ne", &test_d_option_int},
	{"gt", &test_d_option_int},
	{"ge", &test_d_option_int},
	{"lt", &test_d_option_int},
	{"le", &test_d_option_int},
	{"nt", &test_d_option_nt},
	{"ot", &test_d_option_ot},
	{"ef", &test_d_option_ef}
};

static int		ft_string_tests(int argc, char **argv)
{
	if (**argv != '\0' && argc == 1)
		return (e_success);
	else if (((ft_strcmp(argv[1], "=") == e_success)
	|| (ft_strcmp(argv[1], "==") == e_success)) && argc == 3)
		return ((ft_strcmp(argv[0], argv[2]) == 0) ? e_success : e_failure);
	else if ((ft_strcmp(argv[1], "!=") == e_success) && argc == 3)
		return ((ft_strcmp(argv[0], argv[2]) != 0) ? e_success : e_failure);
	else if ((ft_strcmp(argv[1], ">") == e_success) && argc == 3)
		return ((ft_strcmp(argv[0], argv[2]) < 0) ? e_success : e_failure);
	else if ((ft_strcmp(argv[1], "<") == e_success) && argc == 3)
		return ((ft_strcmp(argv[0], argv[2]) > 0) ? e_success : e_failure);
	else if (argc == 2)
		ft_printf("42sh: test: %s: unary operator expected\n", argv[0]);
	else if (argc == 3)
		ft_printf("42sh: test: %s: binary operator expected\n", argv[1]);
	else
		ft_printf("42sh: test: too many arguments\n");
	return (e_error);
}

static int		ft_init_str(char *str[])
{
	str[0] = "==";
	str[1] = "!=";
	str[2] = ">";
	str[3] = ">=";
	str[4] = "<";
	str[5] = "<=";
	return (e_success);
}

static int		ft_dispatch_d_option(char **argv, int nbr_opt, int argc)
{
	int		i;
	char	*str[9];

	i = 0;
	ft_init_str(&str[0]);
	if ((int)ft_strlen(argv[1]) == 3)
	{
		while (i < nbr_opt)
		{
			if (ft_strcmp(g_test_d_opt[i].d_opt, &argv[1][1]) == e_success)
			{
				if (g_test_d_opt[i].double_opt(argv, str[i]) == e_success)
					return (e_success);
				else
					return (e_failure);
			}
			i++;
		}
	}
	(argc < 4)
	? ft_printf("42sh: test: %s: binary operator expected\n", argv[1])
	: ft_printf("42sh: test: too many arguments\n");
	return (e_error);
}

static int		ft_dispatch_s_option(char **argv, int nbr_opt)
{
	int	i;

	i = 0;
	if ((int)ft_strlen(argv[0]) == 2)
	{
		while (i < nbr_opt)
		{
			if (ft_strcmp(g_test_s_opt[i].s_opt, &argv[0][1]) == e_success)
			{
				if (g_test_s_opt[i].single_opt(argv) == e_success)
					return (e_success);
				else
					return (e_failure);
			}
			i++;
		}
	}
	ft_printf("42sh: test: %s: unary operator expected\n", argv[0]);
	return (e_error);
}

int				return_tests(int argc, char **argv)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < argc)
	{
		if (*argv[i] == '!')
		{
			argc--;
			return ((argv[i + 1] && (ret = return_tests(argc, &argv[i + 1]))
			== e_success) ? e_failure : e_success);
		}
		if (*argv[i] == '-' && argc == 2)
			return (((ret = ft_dispatch_s_option(&argv[i], SINGLE_OPT))
			== e_success) ? e_success : ret);
		if (argc > 2 && *argv[i + 1] == '-')
			return (((ret = ft_dispatch_d_option(&argv[i], DOUBLE_OPT, argc))
			== e_success) ? e_success : ret);
		return (((ret = ft_string_tests(argc, &argv[i]))
		== e_success) ? e_success : ret);
		++i;
	}
	return (ret);
}
