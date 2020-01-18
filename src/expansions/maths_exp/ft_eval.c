/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:33:24 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/18 20:10:40 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "maths_expansion.h"
#include "libft.h"

int		ft_eval_ast(t_maths_ast *ast, int64_t *res, char flag)
{
	t_maths_list	*toklist;

	if ((ast->calc_func))
		return (ast->calc_func(ast->left_cmd, ast->right_cmd, res));
	toklist = ast->tokens;
	if (toklist && (t_maths_token*)toklist->content && flag != NO_TOKEN)
		return (ft_arg_value(((t_maths_token*)toklist->content)->token, res));
	if (flag != MANDATORY_TOKEN)
	{
		*res = 0;
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

char	*ft_construct_expansion(char *arg, char *expansion, size_t var_pos,
																size_t var_len)
{
	size_t		len;
	char		*res;

	len = ft_strlen(expansion);
	/*ft_memcheck(*/res = ft_strnew(len + ft_strlen(arg) - var_len);
	ft_memcpy(res, arg, var_pos);
	ft_memcpy(res + var_pos, expansion, len);
	ft_memcpy(res + len + var_pos, arg + var_len + var_pos,
											ft_strlen(arg + var_pos + var_len));
	free(expansion);
	return (res);
}

int		ft_eval(char *expr, int64_t *res)
{
	int				ret;
	t_maths_list	*list;
	t_maths_ast		*ast;

	*res = 0;
	if (!(list = ft_maths_lexer(expr)))
		return (CONV_FAIL);
	if (ft_maths_parser(list) == CONV_FAIL)
		return (CONV_FAIL);
	ast = ft_new_mathast_node(list);
	if (ft_build_ast(ast, POSSIBLY_TOKEN) == CONV_FAIL)
	{
		ft_free_ast(ast);
		return (CONV_FAIL);
	}
	ret = ft_eval_ast(ast, res, NO_FLAG);
	ft_free_ast(ast);
	return (ret);
}

char	*ft_eval_inner_parentheses(char *expr)
{
	size_t		len;
	size_t		inner_par;
	size_t		end_par;
	int64_t		conv;
	char		*res;

	if (ft_find_inner_expr(expr, &inner_par, &end_par))
	{
		expr[end_par] = '\0';
		len = ft_strlen(expr + inner_par);
//		if (!(*(expr + inner_par + 1)))
//			return (NULL);
		if (ft_eval(expr + inner_par + 1, &conv) == CONV_FAIL)
		{
//			print_error(error de conv)
			return (NULL);
		}
		res = ft_itoa64(conv);
		expr[end_par] = ')';
		res = ft_construct_expansion(expr, res, inner_par, len + 1);
//		ft_strdel(&expr);
		return (res);
	}
	else
		return (NULL);
}
