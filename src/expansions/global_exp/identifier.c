/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_identifier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/03/04 16:42:15 by bprunevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
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
