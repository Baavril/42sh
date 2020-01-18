/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_def.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:35:39 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/18 20:56:53 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_DEF_H
# define MATHS_DEF_H

# include "libft.h"

# define BASE "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@_"
# define DEF_BASE			 "0123456789"
# define OCT_BASE			 "01234567"
# define HEX_BASE			 "0123456789abcdef"
# define IFS				" \t"
# define OPERATOR			"+-*/%=<>&|(),^!~"

# define IS_OP				1
# define IS_ARG				0

# define NO_FLAG			0
# define MANDATORY_TOKEN	1
# define NO_TOKEN			2
# define POSSIBLY_TOKEN		3

# define INCR_PRIO			1
# define POSTCR_PRIO		1
# define PRECR_PRIO			2
# define NEG_PRIO			3
# define EXP_PRIO			3
# define MUL_PRIO			5
# define ADD_PRIO			6
# define SH_PRIO			7
# define CMP_PRIO			8
# define EQ_PRIO			9
# define BWAND_PRIO			10
# define BWXOR_PRIO			11
# define BWOR_PRIO			12
# define LOGAND_PRIO		13
# define LOGOR_PRIO			14
# define ASSIGN_PRIO		16
# define COMMA_PRIO			17

# define CONV_SUCCESS		1
# define CONV_FAIL			0

# define LEFT				1
# define RIGHT				0

typedef int				(t_ft_maths)(void *, void *, int64_t *);

typedef struct			s_set_var
{
	char				*var_name;
	int64_t				value;
}						t_set_var;

typedef struct			s_maths_op
{
	char				*op;
	t_ft_maths			*ft_op;
	int					priority;
	int					l_flag;
	int					r_flag;
}						t_maths_op;

typedef struct			s_maths_token
{
	char				*token;
	int					prio;
}						t_maths_token;

typedef struct			s_maths_list
{
	t_maths_token		*content;
	size_t				content_size;
	struct s_maths_list	*next;
}						t_maths_list;

typedef struct			s_maths_ast
{
	t_maths_list		*tokens;
	int64_t				res;
	t_ft_maths			*calc_func;
	struct s_maths_ast	*left_cmd;
	struct s_maths_ast	*right_cmd;
}						t_maths_ast;

#endif
