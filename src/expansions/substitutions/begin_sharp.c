/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsharp_substitutions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprunev <bprunev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by bprunev           #+#    #+#             */
/*   Updated: 2020/01/26 20:02:10 by bprunev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

extern struct s_svar	*g_svar;

int						bsharp_exp(char **token)
{
	struct s_svar	*tmp;

	tmp = g_svar;
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 3, ft_strlen(g_svar->key) - 1) == 0
		&& check_next_var(g_svar->key, token, 2) == SUCCESS)
		{
			ft_strdel(token);
			if (!(*token = ft_itoa(ft_strlen(g_svar->value))))
				return (ERROR);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	g_svar = tmp;
	ft_strdel(token);
	if (!(*token = ft_itoa(0)))
		return (ERROR);
	return (SUCCESS);
}
