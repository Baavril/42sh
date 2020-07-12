/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 16:40:47 by baavril           #+#    #+#             */
/*   Updated: 2020/07/12 23:47:11 by tgouedar         ###   ########.fr       */
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

static int	quoted_linker(struct s_quoted *voyager, char **tokens, char **splitok, int flag)
{
	char			*tmp_to_free;
	char			*tmp_to_free_2;

	tmp_to_free = ft_strdup(*tokens);
	ft_strdel(&(*tokens));
	tmp_to_free_2 = expansions_management(splitok, voyager->expand, flag);
	*tokens = ft_strjoin(tmp_to_free, tmp_to_free_2);
	ft_strdel(&tmp_to_free);
	ft_strdel(&tmp_to_free_2);
	return (0);
}

static int	expansions_quoted_treatment(char **tokens, char **splitok, int flag)
{
	struct s_quoted		*voyager;

	token_quotes_generator(*tokens);
	voyager = g_quoted;
	ft_strdel(tokens);
	while (voyager)
	{
		if (!(splitok = ft_expsplit(voyager->token)))
			return (ERROR);
		if (*tokens == NULL)
			*tokens = expansions_management(splitok, voyager->expand, flag);
		else
			quoted_linker(voyager, tokens, splitok, flag);
		voyager = voyager->next;
	}
	return (0);
}

/*
** The flag int value in the functions of this file is there to
** single out the case of heredoc tokens (since they are unquoted, unslashed)
** but variables are not expanded
*/

int			expansions_treatment(char **tokens, int flag)
{
	char	**splitok;

	splitok = NULL;
	if (!flag && **tokens == TILDE)
		tilde_exp(tokens);
	if (*tokens && (ft_isin(DQUOTES, *tokens) || ft_isin(SQUOTES, *tokens)))
	{
		expansions_quoted_treatment(tokens, splitok, flag);
		free_quoted_token_lst();
	}
	else 
	{
		if (!(splitok = ft_expsplit(*tokens)))
			return (ERROR);
		ft_strdel(tokens);
		*tokens = expansions_management(splitok, 0, flag);
	}
	return (SUCCESS);
}
