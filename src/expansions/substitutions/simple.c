/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_substitutions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/03/01 11:48:05 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

extern struct s_svar		*g_svar;
extern struct s_pos	*g_pos;

static int	simple_special_params(char **token)
{
	char			*tmp1;
	struct s_pos	*ptr;

	tmp1 = NULL;
	ptr = g_pos;
	while (g_pos)
	{
		if (ft_strncmp(g_pos->key, *token + 2, 2) == 0)
		{
			tmp1 = ft_strdup(g_pos->value);
			break ;
		}
		g_pos = g_pos->next;
	}
	g_pos = ptr;
	if (tmp1)
	{
		ft_strdel(token);
		*token = (tmp1) ? ft_strdup(tmp1) : ft_strdup(EMPTY_STR);
		ft_strdel(&tmp1);
		return (SUCCESS);
	}
	return (ERROR);
}

int			simple_exp(char **token)
{
	struct s_svar	*tmp;

	tmp = g_svar;
	if (simple_special_params(token) == SUCCESS)
		return (SUCCESS);
	while (g_svar)
	{
		if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
		&& check_next_var(g_svar->key, token, 1) == SUCCESS)
		{
			ft_strdel(token);
			if (!(*token = ft_strdup(g_svar->value)))
				return (ERROR);
			g_svar = tmp;
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	if (!(*token = ft_strdup(EMPTY_STR)))
		return (ERROR);
	g_svar = tmp;
	return (SUCCESS);
}
