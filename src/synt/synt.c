/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:39 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/21 19:02:47 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "synt_const.h"

static int	operator_check(char *token)
{
	int	i;

	i = 0;
	while (g_operator[i].gram_op[0])
	{
		if (ft_strstr(token, g_operator[i].gram_op))
		{
			psherror(e_syntax_error, g_operator[i].gram_op, e_parsing_type);
			return (g_errordesc[e_syntax_error].code);
		}
		++i;
	}
	return (e_success);
}

int			synt(char **cmd_line)
{
	int i;

	i = 0;
	if (!cmd_line)
	{
		psherror(e_invalid_input, NULL, e_invalid_type);
		return (g_errordesc[e_invalid_input].code);
	}
	while (cmd_line[i])
	{
		if (operator_check(cmd_line[i]))
			return (g_errordesc[e_syntax_error].code);
		++i;
	}
	return (g_errordesc[e_success].code);
}
