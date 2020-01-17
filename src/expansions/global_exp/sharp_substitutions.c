/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sharp_substitutions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/01/14 16:18:20 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "shell_variables.h"
#include "builtins.h"
#include "libft.h"

static int
	check_sharp_var(char **token, char *word, struct s_svar *tmp, int flag)
{
	if (ft_strncmp(g_svar->key, *token + 2, ft_strlen(g_svar->key) - 1) == 0
	&& check_next_var(g_svar->key, token, 1) == SUCCESS)
	{
		ft_strdel(token);
		*token = ft_strdup(matching_ret(g_svar->value, word, flag));
		g_svar = tmp;
		ft_strdel(&word);
		return (SUCCESS);
	}
	return (ERROR);
}

int		osharp_exp(char **token)
{
	int flag;
	char *word;
	struct s_svar *tmp;

	tmp = g_svar;
	flag = (!(ft_spechrlen(*token))) ? 2 : 1;
	word = ft_strcdup(ft_strchr(*token, SHARP) + flag, CL_BRACE);
	while (g_svar)
	{
		if (check_sharp_var(token, word, tmp, flag) == SUCCESS)
			return (SUCCESS);
		g_svar = g_svar->next;
	}
	ft_strdel(token);
	if (!(*token = ft_strdup(EMPTY_STR)))
		return (ERROR);
	ft_strdel(&word);
	g_svar = tmp;
	return (SUCCESS);
}
