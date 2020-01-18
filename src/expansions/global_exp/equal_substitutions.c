/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal_substitutions.c                              :+:      :+:    :+:   */
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


static int
	check_equal_var(char **token, char *word, char *nod, struct s_svar *tmp)
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
			if (!(*token = (word && *word) ? ft_strdup(word)
			: ft_strdup(EMPTY_STR)))
				return (ERROR);
			g_svar = tmp;
			if (checkvarlst(nod))
				listadd_back(newnodshell(nod, 0));
		}
		g_svar = tmp;
		ft_strdel(&word);
		ft_strdel(&nod);
		return (SUCCESS);
	}
	return (ERROR);
}

int
	equal_exp(char **token)
{
	char			*nod;
	char			*word;
	struct s_svar	*tmp;

	tmp = g_svar;
	if (!(nod = setasvar(*token)))
		return (ERROR);
	word = ft_strcdup(ft_strchr(*token, EQUAL) + 1, CL_BRACE);
	while (g_svar)
	{
		if (check_equal_var(token, word, nod, tmp) == SUCCESS)
			return (SUCCESS);
		g_svar = g_svar->next;
	}
	free(*token);
	if (!(*token = (word && *word) ? ft_strdup(word) : ft_strdup(EMPTY_STR)))
		return (ERROR);
	ft_strdel(&word);
	g_svar = tmp;
	listadd_back(newnodshell(nod, 0));
	ft_strdel(&nod);
	return (SUCCESS);
}
