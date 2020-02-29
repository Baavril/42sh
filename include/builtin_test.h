/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/02/29 16:35:04 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_TEST_H
# define BUILTIN_TEST_H

# define SINGLE_OPT	25
# define DOUBLE_OPT	9

# define E_SUCCESS	0
# define E_FAILURE	1
# define E_ERROR	2
# define UID		0004000
# define GID		0002000
# define SOCK		0140000
# define LINK		0120000
# define STKY		0001000

typedef struct	s_test_s_opt
{
	char		*s_opt;
	int			(*single_opt)(char **);
}				t_test_s_opt;

typedef struct	s_test_d_opt
{
	char		*d_opt;
	int			(*double_opt)(char **, char *);
}				t_test_d_opt;

int				test_s_option_b(char **argv);
int				test_s_option_c(char **argv);
int				test_s_option_d(char **argv);
int				test_s_option_a(char **argv);
int				test_s_option_f(char **argv);
int				test_s_option_g(char **argv);
int				test_s_option_h(char **argv);
int				test_s_option_k(char **argv);
int				test_s_option_n(char **argv);
int				test_s_option_o(char **argv);
int				test_s_option_p(char **argv);
int				test_s_option_r(char **argv);
int				test_s_option_s(char **argv);
int				test_s_option_t(char **argv);
int				test_s_option_u(char **argv);
int				test_s_option_v(char **argv);
int				test_s_option_w(char **argv);
int				test_s_option_x(char **argv);
int				test_s_option_z(char **argv);
int				test_s_option_S(char **argv);
int				test_s_option_O(char **argv);
int				test_s_option_N(char **argv);
int				test_s_option_G(char **argv);

int				test_d_option_int(char **argv, char *str);
int				test_d_option_nt(char **argv, char *str);
int				test_d_option_ot(char **argv, char *str);
int				test_d_option_ef(char **argv, char *str);

int				return_tests(int argc, char **argv);

int				ft_retnbr_opts(char **argv);
char			**split_btw_opts(char **argv, int opt);
char			*ft_ret_optstring(char **argv, int exps);
int				find_next_opt(char **argv, int flag, int init);

int				ft_tabret(char *opts, int *tmp_rets);
int				ft_delalloc(char **argv, int ret);
int				ft_strnlen(char c, char *str);

int				ft_manage_parenthesis(char **argv);

void			ft_free_tabs(char **tab);

#endif
