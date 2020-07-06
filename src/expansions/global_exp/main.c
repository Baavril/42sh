/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:40:47 by baavril           #+#    #+#             */
/*   Updated: 2020/07/06 15:56:50 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell_variables.h"
#include "expansions.h"
#include "libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

struct s_quoted	*g_quoted;

static void	free_quoted_token_lst(void)
{
	struct s_quoted *tmp;

	while (g_quoted)
	{
		ft_strdel(&(g_quoted->token));
		tmp = g_quoted->next;
		free(g_quoted);
		g_quoted = tmp;
	}
}

static int	quoted_linker(char **tokens, char **splitok)
{
	char			*tmp_to_free;
	char			*tmp_to_free_2;

	tmp_to_free = ft_strdup(*tokens);
	ft_strdel(&(*tokens));
	tmp_to_free_2 = expansions_management(splitok, g_quoted->expand, 0);
	*tokens = ft_strjoin(tmp_to_free, tmp_to_free_2);
	ft_strdel(&tmp_to_free);
	ft_strdel(&tmp_to_free_2);
	return (0);
}

static int	expansions_quoted_treatment(char **tokens, char **splitok)
{
	struct s_quoted		*tmp;

	token_quotes_generator(*tokens);
	tmp = g_quoted;
	ft_strdel(tokens);
	while (g_quoted)
	{
		if (!(splitok = ft_expsplit(g_quoted->token, DOLLAR)))
			return (ERROR);
		if (*tokens == NULL)
			*tokens = expansions_management(splitok, g_quoted->expand, 0);
		else
			quoted_linker(tokens, splitok);
		g_quoted = g_quoted->next;
	}
	g_quoted = tmp;
	return (0);
}

int			expansions_treatment(char **tokens, int flag)
{
	char	**splitok;

	splitok = NULL;
	if (!flag && **tokens == TILDE)
		tilde_exp(tokens);
	if (!flag && (*tokens && ((ft_isin(DQUOTES, *tokens))
	|| ft_isin(SQUOTES, *tokens))))
	{
		expansions_quoted_treatment(tokens, splitok);
		free_quoted_token_lst();
	}
	else
	{
		if (!(splitok = ft_expsplit(*tokens, DOLLAR)))
			return (ERROR);
		ft_strdel(tokens);
		*tokens = expansions_management(splitok, 0, flag);
	}
	return (SUCCESS);
}
