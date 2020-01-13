/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_dispatcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 13:08:40 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/13 21:00:30 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_dispatcher.h"
#include "maths_def.h"

t_maths_op		g_maths[] =
{
	{">>=", ft_r_shift_assign, ASSIGN_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"<<=", ft_l_shift_assign, ASSIGN_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"+=", ft_add_assign, ASSIGN_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"-=", ft_sub_assign, ASSIGN_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"*=", ft_mul_assign, ASSIGN_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"/=", ft_div_assign, ASSIGN_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"%=", ft_mod_assign, ASSIGN_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"&=", ft_bitwiseand_assign, ASSIGN_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"^=", ft_bitwisexor_assign, ASSIGN_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"|=", ft_bitwiseor_assign, ASSIGN_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"++", ft_incr, INCR_PRIO, POSSIBLY_TOKEN, POSSIBLY_TOKEN},
	{"--", ft_decr, INCR_PRIO, POSSIBLY_TOKEN, POSSIBLY_TOKEN},
	{"**", ft_exp, EXP_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{">>", ft_r_shift, SH_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"<<", ft_l_shift, SH_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"||", ft_logic_or, LOGOR_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"&&", ft_logic_and, LOGAND_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"!=", ft_diff_test, EQ_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"==", ft_eq_test, EQ_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"<=", ft_cmpinfeq_test, CMP_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{">=", ft_cmpsupeq_test, CMP_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"<", ft_cmpinf_test, CMP_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{">", ft_cmpsup_test, CMP_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"+", ft_add, ADD_PRIO, POSSIBLY_TOKEN, MANDATORY_TOKEN},
	{"-", ft_sub, ADD_PRIO, POSSIBLY_TOKEN, MANDATORY_TOKEN},
	{"*", ft_mul, MUL_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"/", ft_div, MUL_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"%", ft_mod, MUL_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"!", ft_logic_neg, NEG_PRIO, NO_TOKEN, MANDATORY_TOKEN},
	{"~", ft_bitwise_neg, NEG_PRIO, NO_TOKEN, MANDATORY_TOKEN},
	{"|", ft_bitwise_or, BWAND_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"&", ft_bitwise_and, BWOR_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"=", ft_assign, ASSIGN_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{"^", ft_bitwise_xor, BWXOR_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{",", ft_comma, COMMA_PRIO, MANDATORY_TOKEN, MANDATORY_TOKEN},
	{NULL, NULL, 0, 0, 0}
};

int				ft_get_op_priority(char *op)
{
	size_t		i;

	i = 0;
	while ((g_maths[i].op))
	{
		if (!(ft_strcmp(g_maths[i].op, op)))
			return (g_maths[i].priority);
		i++;
	}
	return (0);
}

size_t			ft_op_len(char *word)
{
	size_t		i;
	size_t		len;

	i = 0;
	while ((g_maths[i].op))
	{
		len = ft_strlen(g_maths[i].op);
		if (!(ft_strncmp(g_maths[i].op, word, len)))
			return (len);
		i++;
	}
	return (1);
}

t_ft_maths		*ft_op_func(char *op)
{
	size_t		i;

	i = 0;
	while ((g_maths[i].op))
	{
		if (!(ft_strcmp(g_maths[i].op, op)))
			return (g_maths[i].ft_op);
		i++;
	}
	return (NULL);
}

int				ft_get_flag(char side, char *op)
{
	size_t		i;

	i = 0;
	while ((g_maths[i].op))
	{
		if (!(ft_strcmp(g_maths[i].op, op)))
			return (side == LEFT ? g_maths[i].l_flag : g_maths[i].r_flag);
		i++;
	}
	return (0);
}
