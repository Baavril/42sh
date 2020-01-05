/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:12:36 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/12 14:22:35 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_def.h"

static void		ft_rec_depth(const t_maths_ast *ast, size_t *depth)
{
	if (!ast)
		return ;
	*depth += 1;
	ft_rec_depth(ast->left_cmd, depth);
	ft_rec_depth(ast->right_cmd, depth);
}

size_t			ft_ast_depth(const t_maths_ast *ast)
{
	size_t		depth;

	depth = 0;
	ft_rec_depth(ast, &depth);
	return (depth);
}
