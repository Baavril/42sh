/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus_substitutions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/19 12:53:49 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

extern struct s_svar	*g_svar;

static int				check_plus_var(char **token, char *word,
														struct s_svar *tmp)
{
	if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
	&& check_next_var(g_svar->key, token, 1) == SUCCESS)
	{
		ft_strdel(token);
		if (g_svar->value && *(g_svar->value) && word && *word)
		{
			if (!(*token = ft_strdup(word)))
				return (ERROR);
		}
		else
		{
			if (!(*token = ft_strdup(EMPTY_STR)))
				return (ERROR);
		}
		g_svar = tmp;
		ft_strdel(&word);
		return (SUCCESS);
	}
	return (ERROR);
}

int						plus_exp(char **token)
{
	char			*var;
	char			*word;
	struct	s_svar	*tmp;

	tmp = g_svar;
	if (!(var = ft_strcdup(*token + 2, COLON)))
		return (ERROR);
	word = ft_strcdup(ft_strchr(*token, PLUS) + 1, CL_BRACE);
	while (g_svar)
	{
		if (check_plus_var(token, word, tmp) == SUCCESS)
		{
			ft_strdel(&var);
			return (SUCCESS);
		}
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	if (!(*token = ft_strdup(EMPTY_STR)))
		return (ERROR);
	g_svar = tmp;
	ft_strdel(&word);
	ft_strdel(&var);
	return (SUCCESS);
}
