/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsharp_substitutions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/08 13:58:54 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

/* still need to fix the management of positional parameters and arrays. see bash man p 28 */

int		bsharp_exp(char **token)
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
