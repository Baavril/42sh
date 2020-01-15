/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:51:16 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/15 15:15:38 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "maths_interne.h"
#include "error.h"

extern char		*g_exptok;

t_maths_ast		*ft_new_mathast_node(t_maths_list *tokens)
{
	t_maths_ast		*new_node;

	/*ft_memcheck*/new_node = (t_maths_ast*)malloc(sizeof(*new_node));
	new_node->tokens = tokens;
	new_node->calc_func = NULL;
	new_node->left_cmd = NULL;
	new_node->right_cmd = NULL;
	return (new_node);
}

t_maths_list	*ft_get_max_prio(t_maths_list *list)
{
	int				prio;
	int				cur_prio;
	t_maths_list	*res;

	prio = -1;
	res = NULL;
	while (list)
	{
		cur_prio = ((t_maths_token*)list->content)->prio;
		if ((cur_prio) && cur_prio >= prio)
		{
			prio = cur_prio;
			res = list;
		}
		list = list->next;
	}
	return (res);
}

int				ft_build_ast(t_maths_ast *ast, int flag)
{
	t_maths_list		*mid_op;
	t_maths_list		*list;

	list = ast->tokens;
	if (!list && flag == MANDATORY_TOKEN)
	{
		psherror(e_missing_operand, g_exptok, e_maths_type);
		return (CONV_FAIL);
	}
	if (list && flag == NO_TOKEN)
	{
		psherror(e_arg_to_unary, g_exptok, e_maths_type);
		return (CONV_FAIL);
	}
	if (!list)
		return (CONV_SUCCESS);
	mid_op = ft_get_max_prio(list);
	if (!mid_op)
	{
		if (!(list->next))
			return (CONV_SUCCESS);
		psherror(e_missing_operator, g_exptok, e_maths_type);
		return (CONV_FAIL);
	}
	ast->calc_func = ft_op_func(mid_op->content->token);
	ast->right_cmd = ft_new_mathast_node(mid_op->next);
	if (list != mid_op)
	{
		while (list->next != mid_op)
			list = list->next;
		list->next = NULL;
		ast->left_cmd = ft_new_mathast_node(ast->tokens);
	}
	else
		ast->left_cmd = ft_new_mathast_node(NULL);
	mid_op->next = NULL;
	return (ft_build_ast(ast->left_cmd, ft_get_flag(LEFT, mid_op->content->token)) == CONV_SUCCESS
			&& ft_build_ast(ast->right_cmd, ft_get_flag(RIGHT, mid_op->content->token)) == CONV_SUCCESS);
}
