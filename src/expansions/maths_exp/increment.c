/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:50:32 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/18 21:14:11 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_expansion.h"

extern t_list	*g_post_incr;

static int		ft_update_setvalue(char *var_name, int64_t res)
{
	t_set_var	*set_nod;
	t_list		*voyager;

	voyager = g_post_incr;
	while (voyager)
	{
		set_nod = (t_set_var*)(voyager->content);
		if (!ft_strcmp(set_nod->var_name, var_name))
		{
			set_nod->value = res;
			return (1);
		}
		voyager = voyager->next;
	}
	return (0);
}

static void		ft_add_incrlst(char *var_name, int64_t res)
{
	t_set_var	new;

	if (ft_update_setvalue(var_name, res))
		return ;
	new.var_name = ft_strdup(var_name);
	new.value = res;
	ft_lstadd(&g_post_incr, ft_lstnew(&new, sizeof(new)));
}

void			ft_set_and_pop(void *content, size_t size)
{
	t_set_var	*assig;

	(void)size;
	assig = (t_set_var*)content;
	setshvar(assig->var_name, assig->value);
	ft_strdel(&(assig->var_name));
}

int				ft_incr(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, NO_TOKEN) == CONV_SUCCESS)
	{
		*res = left;
		setshvar(((t_maths_ast*)(left_cmd))->tokens->content->token, left + 1);
		return (CONV_SUCCESS);
	}
	if (ft_eval_ast(left_cmd, &left, NO_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = right + 1;
		ft_add_incrlst(((t_maths_ast*)left_cmd)->tokens->content->token, *res);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}

int				ft_decr(void *left_cmd, void *right_cmd, int64_t *res)
{
	int64_t		left;
	int64_t		right;

	if (ft_eval_ast(left_cmd, &left, MANDATORY_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, NO_TOKEN) == CONV_SUCCESS)
	{
		*res = left;
		setshvar(((t_maths_ast*)(left_cmd))->tokens->content->token, left - 1);
		return (CONV_SUCCESS);
	}
	if (ft_eval_ast(left_cmd, &left, NO_TOKEN) == CONV_SUCCESS
	&& ft_eval_ast(right_cmd, &right, MANDATORY_TOKEN) == CONV_SUCCESS)
	{
		*res = right - 1;
		ft_add_incrlst(((t_maths_ast*)left_cmd)->tokens->content->token, *res);
		return (CONV_SUCCESS);
	}
	return (CONV_FAIL);
}
