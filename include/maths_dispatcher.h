/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_dispatcher.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 13:08:38 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/05 11:29:51 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_DISPATCHER
# define MATHS_DISPATCHER

#include <stdint.h>
#include "maths_def.h"


int				ft_r_shift(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_l_shift(void *left_cmd, void *right_cmd, int64_t *res);

int				ft_logic_neg(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_logic_and(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_logic_or(void *left_cmd, void *right_cmd, int64_t *res);

int				ft_eq_test(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_diff_test(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_cmpinf_test(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_cmpinfeq_test(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_cmpsup_test(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_cmpsupeq_test(void *left_cmd, void *right_cmd, int64_t *res);

int				ft_add(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_sub(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_mul(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_exp(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_div(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_mod(void *left_cmd, void *right_cmd, int64_t *res);

int				ft_bitwise_neg(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_bitwise_and(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_bitwise_or(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_bitwise_xor(void *left_cmd, void *right_cmd, int64_t *res);

int				ft_incr(void *left_cmd, void *right_cmd, int64_t *res);
int				ft_decr(void *left_cmd, void *right_cmd, int64_t *res);

int				ft_comma(void *left_cmd, void *right_cmd, int64_t *res);

int		ft_assign(void *left_cmd, void *right_cmd, int64_t *res);
int		ft_r_shift_assign(void *left_cmd, void *right_cmd, int64_t *res);
int		ft_l_shift_assign(void *left_cmd, void *right_cmd, int64_t *res);
int		ft_add_assign(void *left_cmd, void *right_cmd, int64_t *res);
int		ft_sub_assign(void *left_cmd, void *right_cmd, int64_t *res);
int		ft_mul_assign(void *left_cmd, void *right_cmd, int64_t *res);
int		ft_div_assign(void *left_cmd, void *right_cmd, int64_t *res);
int		ft_mod_assign(void *left_cmd, void *right_cmd, int64_t *res);
int		ft_bitwiseand_assign(void *left_cmd, void *right_cmd, int64_t *res);
int		ft_bitwiseor_assign(void *left_cmd, void *right_cmd, int64_t *res);
int		ft_bitwisexor_assign(void *left_cmd, void *right_cmd, int64_t *res);

#endif
