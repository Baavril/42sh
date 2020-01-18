/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 19:38:58 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/18 20:10:54 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_expansion.h"

void		ft_free_ast(t_maths_ast *ast)
{
	if (!ast)
		return ;
	ft_free_ast(ast->left_cmd);
	ft_free_ast(ast->right_cmd);
	ft_lstdel((t_list**)(&(ast->tokens)), &ft_free_token);
	ft_memdel((void**)&ast);
}
