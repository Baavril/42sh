/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_identifier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/08 18:31:11 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "builtin_test.h"
#include "expansions.h"
#include "libft.h"

int		identifier(char *token)
{
	if (*token == DOLLAR)
	{
		if (check_braces(token + 1) == SIMPLE_EXP)
		{
			if (check_colon(token + 1) == COMPLEX_EXP)
				return (check_colon_symbol(token + 1));
			return (check_symbol(token + 1));
		}
		else if (check_maths(token + 1) != ERROR)
			return (MATHS_EXP);
		return (DIRECT_EXP);
	}
	return (ERROR);
}
