/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dash_substitutions.c                               :+:      :+:    :+:   */
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

static int		check_dash_var(char **token, char *word, struct s_svar *tmp)
{
	if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
	&& check_next_var(g_svar->key, token, 1) == SUCCESS)
	{
		ft_strdel(token);
		if (g_svar->value && *(g_svar->value))
		{
			if (!(*token = ft_strdup(g_svar->value)))
				return (ERROR);
		}
		else
		{
			if (!(*token = (word && *word) ? ft_strdup(word) : ft_strdup(EMPTY_STR)))
				return (ERROR);
		}
		g_svar = tmp;
		return (SUCCESS);
	}
	return (ERROR);
}

int				dash_exp(char **token)
{
	char			*var;
	char			*word;
	struct s_svar	*tmp;

	tmp = g_svar;
	if (!(var = ft_strcdup(*token + 2, COLON)))
		return (ERROR);
	word = ft_strcdup(ft_strchr(*token, DASH) + 1, CL_BRACE);
	while (g_svar)
	{
		if (check_dash_var(token, word, tmp) == SUCCESS)
		{
			ft_strdel(&var);
			ft_strdel(&word);
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	if (!(*token = (word && *word) ? ft_strdup(word) : ft_strdup(EMPTY_STR)))
		return (ERROR);
	g_svar = tmp;
	ft_strdel(&word);
	ft_strdel(&var);
	return (SUCCESS);
}
